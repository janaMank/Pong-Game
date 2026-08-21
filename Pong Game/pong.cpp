#include <raylib.h>


int player1 = 0;
int player2 = 0;


class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;

	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}

	void Update() {
		x += speed_x;
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1;
		}

		//Point Player 1
		if (x + radius >= GetScreenWidth()) {
			player1++;
			ResetBall();
		}

		//Point Player 2	
		if (x - radius <= 0) {
			player2++;
			ResetBall();
		}
	}

	void ResetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_choices[2] = { -1, 1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)];
		speed_x *= speed_choices[GetRandomValue(0, 1)];
	}
};


class Paddle {
public:
	float x, y;
	float width, height;
	int speed;

	void Draw() {
		DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);

	}

	void Move(KeyboardKey up, KeyboardKey down) {

		if (IsKeyDown(up)) {
			y = y - speed;
		}
		if (IsKeyDown(down)) {
			y = y + speed;
		}
		if (y <= 0) {
			y = 0;
		}
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}


};

Ball ball;
Paddle r_Paddle;
Paddle l_Paddle;

int main() {
	//Konstanten setzen
	const int screen_width = 1280;
	const int screen_height = 800;
	const int paddle_height = 100;
	const int y_center_paddle = screen_height / 2 - paddle_height / 2;
	//Variablen setzen
	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_y = 7;
	ball.speed_x = 7;

	r_Paddle.height = 120;
	r_Paddle.width = 20;
	r_Paddle.y = y_center_paddle;
	r_Paddle.x = screen_width - r_Paddle.width - 10;
	r_Paddle.speed = 6;

	l_Paddle.height = 120;
	l_Paddle.width = 20;
	l_Paddle.y = y_center_paddle;
	l_Paddle.x = 10;
	l_Paddle.speed = 6;



	InitWindow(screen_width, screen_height, "PingPongGame");
	SetTargetFPS(40);

	while (!WindowShouldClose())
	{


		// Positions
		ball.Update();
		r_Paddle.Move(KEY_UP, KEY_DOWN);
		l_Paddle.Move(KEY_W, KEY_S);

		// Collision Check
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ r_Paddle.x, r_Paddle.y, r_Paddle.width, r_Paddle.height })) {
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ l_Paddle.x, l_Paddle.y, l_Paddle.width, l_Paddle.height })) {
			ball.speed_x *= -1;
		}


		// Drawing

		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Ping Pong!", 0, 0, 20, WHITE);
		DrawText(TextFormat("%i", player1), screen_width / 4, 20, 50, WHITE);
		DrawText(TextFormat("%i", player2), 3 * screen_width / 4, 20, 50, WHITE);
		DrawLine(screen_width / 2, 0, screen_width / 2, 800, GRAY);
		ball.Draw();
		r_Paddle.Draw();
		l_Paddle.Draw();



		EndDrawing();


	}

	CloseWindow();

	return 0;
}