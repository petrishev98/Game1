#include <SFML/Graphics.hpp>
#include <iostream>

#define LENGTH 8
#define BLACK_PAWN 1
#define WHITE_PAWN -1


using namespace sf;
using namespace std;

class pawn
{
private:
	float x = 0;//��������� ���������� �
	float y = 0;//��������� ���������� �
	int color;//0 �����, 1 ������
	
	int matrixi;
	int matrixj;
	Image image;
	Texture texture;
	Sprite sprite;
	int matrix1[8][8] =
	{
0, 0, 0, 1, 2, 3, 4, 5,
0, 0, 0, 1, 2, 3, 4, 5,
0, 0, 0, 1, 2, 3, 4, 5,
1, 1, 1, 2, 3, 4, 5, 6,
2, 2, 2, 3, 4, 5, 6, 7,
3, 3, 3, 4, 5, 6, 7, 8,
4, 4, 4, 5, 6, 7, 8, 9,
5, 5, 5, 6, 7, 8, 9, 10
	};
public:

	pawn()
	{

	}
	
	bool take = 0;
	int getMatrixx()
	{
		if (matrix1[this->matrixi - 1][this->matrixj] < matrix1[this->matrixi][this->matrixj])
			return 1;//����� �����, ��� ������ ����� �����
		else if (matrix1[this->matrixi][this->matrixj - 1] < matrix1[this->matrixi][this->matrixj])
			return -1;//����� �����
		else if (matrix1[this->matrixi][this->matrixj] == 0)
			return 0;//�� ��� � ���������� ����
		else return 2;//��� �������� ����
	}

	int getMatrixi()
	{
		return matrixi;
	}
	int getMatrixj()
	{
		return matrixj;
	}
	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	bool getColor()
	{
		return color;
	}

	Sprite getSprite()
	{
		return sprite;
	}
	float getPosition_x()
	{
		return sprite.getPosition().x;
	}
	float getPosition_y()
	{
		return sprite.getPosition().y;
	}

	float setX(float X)
	{
		return x = X;
	}
	int setMatrixi(int i)
	{

		return this->matrixi = i;
	}
	int setMatrixj(int j)
	{
		return this->matrixj = j;
	}


	float setY(float Y)
	{
		return this->y = Y;
	}

	void setColor(bool c)
	{
		this->color = c;
		switch (color)
		{
		case 0:
			image.loadFromFile("images/White_pawn.png");
			image.createMaskFromColor(Color(255, 255, 255));
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			break;
		case 1:
			image.loadFromFile("images/Black_pawn.png");
			image.createMaskFromColor(Color(255, 255, 255));
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			break;

		}

	}

	Sprite setSprite(Sprite spr)
	{
		return this->sprite = spr;
	}

	
	void setPosition(float a, float b)
	{
		sprite.setPosition(a, b);
	}

};



class Game : public pawn
{
private:
	int whoMotion;//������ ������, ������� ����� ���������
	
	bool Motion = false;//��� ���, 0 - �����, 1 - ������
	
	bool win = false;
	bool lose = false;
	
public:
	
	bool getWin()
	{
		return win;
	}
	bool getLose()
	{
		return lose;
	}
	
	int getwhoMotion()
	{
		return whoMotion;
	}
	
	bool getMotion()
	{
		return Motion;
	}
	
	bool setMotion(bool h)
	{
		return this->Motion = h;
	}
	bool setWin(bool i)
	{
		return this->win = i;
	}
	bool setLose(bool i)
	{
		return this->lose = i;
	}
	
	
	int setwhoMotion(int i)
	{
		return this->whoMotion = i;
	}
	
	void setData()
	{

	}

};


int main()
{
	setlocale(LC_ALL, "Russian");
	RenderWindow window(VideoMode(512, 512), "test");

	// ������ ������������ ������� ������ (����� ������ �������� ����� ���� ���������)
	window.setFramerateLimit(60);



	// ������� ������ ����� - 64 �������
	int blockWidht = 64;

	




	
	const int n = 9;
	
	bool isMove = false;//���������� ��� ������ ���� �� �������
	float dX = 0;//������������� �������� �� �
	float dY = 0;//�� �
	float x = 0, y = 0, X, Y;
	pawn Wh[n]; 
	pawn Bl[n];
	Game game;

	//������ ��������� ������� � ��������� � ������� ��� ������
	for (int i = 0; i <= 8; i++)
	{
		Wh[i].setColor(0);
		Bl[i].setColor(1);
	}

	int z = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			Wh[z].setX(64 * i);
			Wh[z].setY(64 * j);
			Bl[z].setX(448 - 64 * i);
			Bl[z].setY(448 - 64 * j);
			Wh[z].setPosition(64 * i, 64 * j);
			Bl[z].setPosition(448 - 64 * i, 448 - 64 * j);
			Bl[z].setMatrixi(7-j);
			Bl[z].setMatrixj(7-i);

			z++;
		}
	}
	

	
	
	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		
		// �������� � �������� ��������
		Texture board;
		board.loadFromFile("Images/Board.png");
		//board.loadFromFile("D:\\�����\\������ VS17 ��������\\Project2\\Project2\\Images\\Board.png");

		Sprite Board(board);
		
		
		
		// ������������ ������� � �����
		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		//int i=0;
		
		Event event;
		while (window.pollEvent(event))
		{

			
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
			{
				if (event.key.code == Mouse::Left)//� ������ �����
				{
					for (int i = 0; i <= 8; i++)
					{

						if (Wh[i].getSprite().getGlobalBounds().contains(pixelPos.x, pixelPos.y))//� ��� ���� ���������� ������� �������� � ������
						{

							X = x;
							Y = y;
							
							dX = pixelPos.x - Wh[i].getPosition_x();//������ �������� ����� �������� ������� � �������.��� ������������� �������
							dY = pixelPos.y - Wh[i].getPosition_y();//���� ����� �� y
							isMove = true;//����� ������� ������
							Wh[i].take = 1;
						
						}
					}
				}
			}
			
			
			if (event.type == Event::MouseButtonReleased)//���� ��������� �������
			{
				int possibleMoves = 0;
				for (int i = 0; i <= 8; i++)
				{
					//for (int j = 0; j <= 8; j++)
					//{

					//���� �� ������, �������� �������, � ����� ������, ����� ������� ������� ��� �������� i, �� ������� ������ 
					if (event.key.code == Mouse::Left && (Wh[i].getSprite().getGlobalBounds().contains(pixelPos.x, pixelPos.y) || Bl[i].getSprite().getGlobalBounds().contains(pixelPos.x, pixelPos.y)))
					{
						possibleMoves++;
						
						if (Bl[i].getSprite().getGlobalBounds().contains(pixelPos.x, pixelPos.y))//���� ������ � ������ ������ ��� �������� i
						{
							possibleMoves++;
							
						}
					}
					
				}
				
				//���� �����, ������
				for (int i = 0; i <= 8; i++)
				{
					if (event.key.code == Mouse::Left && possibleMoves == 1) //� ������ ����� � ������ �� ������ ������(possibleMovies=1)
					{

						//�������� ��������� ������� � �������� 4 ������, ���� �� ����� - ���������� �� �����
						if (pixelPos.x < 512 && pixelPos.y < 512 && pixelPos.x>0 && pixelPos.y>0 && Wh[i].take)
						{

							//�������
							if (pixelPos.x >= Wh[i].getX() + 64 && pixelPos.x <= Wh[i].getX() + 128 && pixelPos.y <= Wh[i].getY() + 64 && pixelPos.y >= Wh[i].getY())
								
							{

								Wh[i].setPosition(Wh[i].getX() + 64, Wh[i].getY());
								Wh[i].setX(Wh[i].getX() + 64);
								Wh[i].setY(Wh[i].getY());
								game.setMotion(true);
							}
							else //����
								if (pixelPos.y >= Wh[i].getY() + 64 && pixelPos.y <= Wh[i].getY() + 128 && pixelPos.x <= Wh[i].getX() + 64 && pixelPos.x >= Wh[i].getX())
									
								{
									Wh[i].setPosition(Wh[i].getX(), Wh[i].getY() + 64);
									Wh[i].setX(Wh[i].getX());
									Wh[i].setY(Wh[i].getY() + 64);
									game.setMotion(true);
								}
								else  //������
									if (pixelPos.x <= Wh[i].getX() && pixelPos.x >= Wh[i].getX() - 64 && pixelPos.y <= Wh[i].getY() + 64 && pixelPos.y >= Wh[i].getY())
										
									{
										Wh[i].setPosition(Wh[i].getX() - 64, Wh[i].getY());
										Wh[i].setX(Wh[i].getX() - 64);
										Wh[i].setY(Wh[i].getY());							
										game.setMotion(true);
									}
									else //�����
										if (pixelPos.y >= Wh[i].getY() - 64 && pixelPos.y <= Wh[i].getY() && pixelPos.x <= Wh[i].getX() + 64 && pixelPos.x >= Wh[i].getX())
											
										{
											Wh[i].setPosition(Wh[i].getX(), Wh[i].getY() - 64);
											Wh[i].setX(Wh[i].getX());
											Wh[i].setY(Wh[i].getY() - 64);
											game.setMotion(true);
										}
										
										else//���� �� ������ � ������ ���� ���� ����� ��� ������ ��������� ����� �������, �� ���������� �� �����
										{
											Wh[i].setPosition(Wh[i].getX(), Wh[i].getY());//�� �� ����� ������� ������
											Wh[i].take = 0;
											isMove = false;
										}


							
						}
						
					}
					else Wh[i].setPosition(Wh[i].getX(), Wh[i].getY());//���� ������ �� ������ ��� ����� ������, possibleMovies>1
					Wh[i].take = 0;
					isMove = false;
					
				}
			}
		}

		if (isMove) //���� ����� �������
		{
				for(int i=0;i<=8;i++)
				{
					if (Wh[i].take) //���� ������, ������� ����� ����� �����
					{
						Wh[i].setPosition(pixelPos.x - dX, pixelPos.y - dY);//�������
						
					}
				}
		
			
		}




		//AI
		if (game.getMotion())//���� ��� ��

		{
			bool left = false;
			bool right = false;
			bool up = false;
			bool down = false;
			
			game.setwhoMotion(0);
			int neverMotion = 0;
			int neverMotion2 = 0;
			
			
			
			do//�������� ����������� ���� ������ � �����
			{
				
				
				
				int possibleMovesLeft = 0;
				int possibleMovesUp = 0;
				
				for (int i = 0; i <= 8; i++)
				{
					
					

					// �������� �� ������� �� ����� ��������� �����
					if ((Wh[i].getSprite().getGlobalBounds().contains(Bl[game.getwhoMotion()].getX() - 64, Bl[game.getwhoMotion()].getY()) || Bl[i].getSprite().getGlobalBounds().contains(Bl[game.getwhoMotion()].getX() - 64, Bl[game.getwhoMotion()].getY())))
					{

						possibleMovesLeft++;
						
					}
					
					
					// �������� �� ������� �� ����� ��������� ������
					if ((Wh[i].getSprite().getGlobalBounds().contains(Bl[game.getwhoMotion()].getX(), Bl[game.getwhoMotion()].getY() - 64) || Bl[i].getSprite().getGlobalBounds().contains(Bl[game.getwhoMotion()].getX(), Bl[game.getwhoMotion()].getY() - 64)))//���� �� ������, �������� �������, � ����� ������, ����� ������� ������� ��� �������� i, �� ������� ������ 
					{

						possibleMovesUp++;
						
					}
					

					

				}

				
				

				if (possibleMovesLeft == 0 && Bl[game.getwhoMotion()].getX() - 64 >= 0)// ���� ������ ����� ����� � �� ������� �� �������
				{
					left = true;
				};

				if (possibleMovesUp == 0 && Bl[game.getwhoMotion()].getY() - 64 >= 0) // ���� ������ ������ ����� � �� ������� �� �������
				{
					up = true;
				};
				
				if (left && up)//���������� �������, ����� ������� ������ ���
				{


					if (Bl[game.getwhoMotion()].getMatrixx() == 1) //���� ����� �����
					{
						

						left = false;
					}
					if (Bl[game.getwhoMotion()].getMatrixx() == -1)//���� ����� ������
					{
						
						up = false;
					}
				};
				
				if (!left && !up) // ���� ������ �� ����� �� �����, �� ����, �� ���� ����� ��������� while, ��������� ���������
				{
				
					int i = game.getwhoMotion();
					i++;
					game.setwhoMotion(i);
					neverMotion++;
					
				};
				
				
				
				
			} while (!left && !up && neverMotion < 9);



			if (!up && !left)//����� ��� �������� � ������ � ������ ����� ��� 0
			{
				
				game.setwhoMotion(0);
				
			};


			//���� ����� ������ � ����� ���
			while ((!right && !down && !up && !left && neverMotion2 < 9))
			{
				
				int possibleMovesRight = 0;
				int possibleMovesDown = 0;
				
				for (int i = 0; i <= 8; i++)
				{
					//�������
					if ((Wh[i].getSprite().getGlobalBounds().contains(Bl[game.getwhoMotion()].getX() + 64, Bl[game.getwhoMotion()].getY()) || Bl[i].getSprite().getGlobalBounds().contains(Bl[game.getwhoMotion()].getX() + 64, Bl[game.getwhoMotion()].getY())))
					{

						possibleMovesRight++;
						
					}

					//����
					if ((Wh[i].getSprite().getGlobalBounds().contains(Bl[game.getwhoMotion()].getX(), Bl[game.getwhoMotion()].getY() + 64) || Bl[i].getSprite().getGlobalBounds().contains(Bl[game.getwhoMotion()].getX(), Bl[game.getwhoMotion()].getY() + 64)))//���� �� ������, �������� �������, � ����� ������, ����� ������� ������� ��� �������� i, �� ������� ������ 
					{

						possibleMovesDown++;
						
					}
					
				}





				if (possibleMovesDown == 0 && Bl[game.getwhoMotion()].getY() + 64 <= 448) // ���� ������ ������ ����� � �� ������� �� �������
				{
					down = true;
					neverMotion2 = 0;
				};
				if (possibleMovesRight == 0 && Bl[game.getwhoMotion()].getX() + 64 <= 448)// ���� ������ ������ ����� � �� ������� �� �������
				{
					right = true;
					neverMotion2 = 0;

				};





				if (right && down)//���������� ������� ��� ������� ����
				{


					if (Bl[game.getwhoMotion()].getMatrixx() == 1)//����� �����, ������ �� � ������ ����� ����� �������
					{
						

						down = false;
						
					}
					if (Bl[game.getwhoMotion()].getMatrixx() == -1)//����� �����, �� � ������� ������ ����� �������, ������� ��� ���� ���� 
					{
						
						right = false;
						
					}
					if (Bl[game.getwhoMotion()].getMatrixx() == 0)//�� ������� ������, ������� ��� �� �����
					{
						
						right = false;
						down = false;
					}
				};

				if (!right && !down) // ���� ������ �� ����� �� �����, �� ����, �� ���� ����� ��������� while, ��������� ���������
				{
					
					int i = game.getwhoMotion();
					i++;
					game.setwhoMotion(i);
					neverMotion2++;
					
				};

			};
				
		
			
		
			

			if (left)
			{
				Bl[game.getwhoMotion()].setPosition(Bl[game.getwhoMotion()].getX() - 64, Bl[game.getwhoMotion()].getY());
				Bl[game.getwhoMotion()].setX(Bl[game.getwhoMotion()].getX() - 64);
				Bl[game.getwhoMotion()].setY(Bl[game.getwhoMotion()].getY());
				
				int j = Bl[game.getwhoMotion()].getMatrixj(); 
				j--;
				Bl[game.getwhoMotion()].setMatrixj(j);
				
				neverMotion = 0;
				
				game.setMotion(false);
			}
			else if (up)
			{
				Bl[game.getwhoMotion()].setPosition(Bl[game.getwhoMotion()].getX(), Bl[game.getwhoMotion()].getY() - 64);
				Bl[game.getwhoMotion()].setX(Bl[game.getwhoMotion()].getX());
				Bl[game.getwhoMotion()].setY(Bl[game.getwhoMotion()].getY() - 64);
				int i = Bl[game.getwhoMotion()].getMatrixi();
				i--;
				Bl[game.getwhoMotion()].setMatrixi(i);
				
				neverMotion = 0;
				
				game.setMotion(false);
			}

			else if (right)
			{
				Bl[game.getwhoMotion()].setPosition(Bl[game.getwhoMotion()].getX() + 64, Bl[game.getwhoMotion()].getY());
				Bl[game.getwhoMotion()].setX(Bl[game.getwhoMotion()].getX() + 64);
				Bl[game.getwhoMotion()].setY(Bl[game.getwhoMotion()].getY());
				int j = Bl[game.getwhoMotion()].getMatrixj();
				j++;
				Bl[game.getwhoMotion()].setMatrixj(j);
	
				neverMotion2 = 0;
				
				game.setwhoMotion(0);
				
				game.setMotion(false);
			}
					
			else if (down)
			{
				Bl[game.getwhoMotion()].setPosition(Bl[game.getwhoMotion()].getX(), Bl[game.getwhoMotion()].getY() + 64);
				Bl[game.getwhoMotion()].setX(Bl[game.getwhoMotion()].getX());
				Bl[game.getwhoMotion()].setY(Bl[game.getwhoMotion()].getY() + 64);
				int i = Bl[game.getwhoMotion()].getMatrixi();
				i++;
				Bl[game.getwhoMotion()].setMatrixi(i);
				
				neverMotion2 = 0;
				
				
				game.setMotion(false);
			}
			
			game.setMotion(false);


			
						
		}
		int bbb = 0;
		int ccc = 0;
		//�������� ������ � ���������, ������� - ��� ������� ��������� � �������� �������� 
		for (int i = 0; i <= 8; i++)
		{
			if (Wh[i].getX() >256 && Wh[i].getY() > 256)
			{
				bbb++;
				
			}
			if (bbb == 9)
			{
				game.setWin(true);

			}

		}
		for (int i = 0; i <= 8; i++)
		{
			if (Bl[i].getX() < 192 && Bl[i].getY() < 192)
			{
				ccc++;
				
			}
			if (ccc == 9)
			{
				game.setLose(true);

			}

		}
	


				// ��������� ����� ���� - �����
			window.clear(Color::White);
			window.draw(Board);
			//��������� ��������� ��� ������ ��� ���������
			if (game.getWin())
			{
				
				system("pause");
			}

			if (game.getLose())
			{
				
				system("pause");
			}
			
			for (int i = 0; i <= 8; i++) //������ �������
			{
				window.draw(Wh[i].getSprite());
				window.draw(Bl[i].getSprite());
				
				
				
			};
				

			
			window.display();

			
			
	}
	
	
	return 0;
} 