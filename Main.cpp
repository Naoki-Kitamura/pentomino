#include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include "Board.hpp"
#include "Mino.hpp"

void Main()
{
	Window::SetTitle(U"Pentomino(alpha)");
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	Array<Mino> m;
	Array<int> order;
	Board b;
	int i, j;

  // initialize mino
	for(i = 0; i < 2; i++) {
		for (j = 0; j < 6; j++) {
			m.push_back(Mino(i * 6 + j, { 60 + 120 * j, 360 + 120 * i }));
			order.push_back(i * 6 + j);
		}
	}

	int grubbed = -1;
	int selected = -1;

	while (System::Update())
	{
		if (grubbed >= 0) {
			selected = grubbed;
			m[grubbed].moveBy(Cursor::Delta());

			if (MouseL.up()) {
				b.SetMino(&m[grubbed]);
				grubbed = -1;
			}
			else if (MouseL.pressed()) {
				if (MouseR.up()) m[grubbed].rotate(1);
		    if (MouseM.up()) m[grubbed].flip();
			}
		}
		else {
			selected = -1;
			for (i = Mino::MINO_NUM-1; i >= 0; i--) {
				if (m[order[i]].mouseOver()) {
					selected = order[i];

					if (MouseL.down()) {
						grubbed = selected;

						b.removeMino(&m[grubbed]);

						order.remove(selected);
						order.push_back(selected);

						break;
					}

					if (MouseR.up()) {
						m[selected].rotate(1);
						order.remove(selected);
						order.push_back(selected);
					}
					if (MouseM.up()) {
						m[selected].flip();
						order.remove(selected);
						order.push_back(selected);
					}
					
					break;
				}
			}
		}

		b.draw();
		for (i = 0; i < Mino::MINO_NUM; i++) {
		  m[order[i]].draw();
		}
		if(selected>=0) m[selected].drawFrame();

	}
}
