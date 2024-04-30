#include<windows.h>
#include <GL/glut.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const float PADDLE_WIDTH = 80.0f;
const float PADDLE_HEIGHT = 10.0f;
float paddle1X = WIDTH / 2.0f;
float paddle1Y = HEIGHT / 10.0f;
float paddle2X = WIDTH / 2.0f;
float paddle2Y = HEIGHT - HEIGHT / 10.0f;
const float BALL_RADIUS = 10.0f;
float ballX = WIDTH / 2.0f;
float ballY = HEIGHT / 2.0f;
float ballSpeedX = 2.0f;
float ballSpeedY = 2.0f;
bool isPaddle1LeftKeyPressed = false;
bool isPaddle1RightKeyPressed = false;
bool isPaddle2LeftKeyPressed = false;
bool isPaddle2RightKeyPressed = false;

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
}

void drawPaddle(float x, float y) {
	glBegin(GL_QUADS);
	glVertex2f(x - PADDLE_WIDTH / 2, y - PADDLE_HEIGHT / 2);
	glVertex2f(x + PADDLE_WIDTH / 2, y - PADDLE_HEIGHT / 2);
	glVertex2f(x + PADDLE_WIDTH / 2, y + PADDLE_HEIGHT / 2);
	glVertex2f(x - PADDLE_WIDTH / 2, y + PADDLE_HEIGHT / 2);
	glEnd();
}

void drawBall() {
	glTranslatef(ballX, ballY, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 360; i++) {
		float angle = i * 3.14159f / 180.0f;
		float x = BALL_RADIUS * cosf(angle);
		float y = BALL_RADIUS * sinf(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	drawPaddle(paddle1X, paddle1Y);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawPaddle(paddle2X, paddle2Y);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawBall();
	glutSwapBuffers();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 'A':
		isPaddle1LeftKeyPressed = true;
		break;
	case 'd':
	case 'D':
		isPaddle1RightKeyPressed = true;
		break;
	case 'j':
	case 'J':
		isPaddle2LeftKeyPressed = true;
		break;
	case 'l':
	case 'L':
		isPaddle2RightKeyPressed = true;
		break;
	}
}

void keyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 'A':
		isPaddle1LeftKeyPressed = false;
		break;
	case 'd':
	case 'D':
		isPaddle1RightKeyPressed = false;
		break;
	case 'j':
	case 'J':
		isPaddle2LeftKeyPressed = false;
		break;
	case 'l':
	case 'L':
		isPaddle2RightKeyPressed = false;
		break;
	}
}

void update(int value) {
	ballX += ballSpeedX;
	ballY += ballSpeedY;

	if (isPaddle1LeftKeyPressed) {
		paddle1X -= 5.0f;
	}
	if (isPaddle1RightKeyPressed) {
		paddle1X += 5.0f;
	}

	if (isPaddle2LeftKeyPressed) {
		paddle2X -= 5.0f;
	}
	if (isPaddle2RightKeyPressed) {
		paddle2X += 5.0f;
	}
	
	if (paddle1X - PADDLE_WIDTH / 2 < 0) {
		paddle1X = PADDLE_WIDTH / 2;
	}
	if (paddle1X + PADDLE_WIDTH / 2 > WIDTH) {
		paddle1X = WIDTH - PADDLE_WIDTH / 2;
	}

	if (paddle2X - PADDLE_WIDTH / 2 < 0) {
		paddle2X = PADDLE_WIDTH / 2;
	}
	if (paddle2X + PADDLE_WIDTH / 2 > WIDTH) {
		paddle2X = WIDTH - PADDLE_WIDTH / 2;
	}

	if (ballX + BALL_RADIUS > WIDTH || ballX - BALL_RADIUS < 0) {
		ballSpeedX = -ballSpeedX;
	}
	if (ballY + BALL_RADIUS > HEIGHT || ballY - BALL_RADIUS < 0) {
		ballSpeedY = -ballSpeedY;
	}

	if (ballY - BALL_RADIUS < paddle1Y + PADDLE_HEIGHT / 2 && ballY + BALL_RADIUS > paddle1Y - PADDLE_HEIGHT / 2 &&
		ballX - BALL_RADIUS < paddle1X + PADDLE_WIDTH / 2 && ballX + BALL_RADIUS > paddle1X - PADDLE_WIDTH / 2) {
		ballSpeedY = -ballSpeedY;
	}

	if (ballY - BALL_RADIUS < paddle2Y + PADDLE_HEIGHT / 2 && ballY + BALL_RADIUS > paddle2Y - PADDLE_HEIGHT / 2 &&
		ballX - BALL_RADIUS < paddle2X + PADDLE_WIDTH / 2 && ballX + BALL_RADIUS > paddle2X - PADDLE_WIDTH / 2) {
		ballSpeedY = -ballSpeedY;
	}

	if (ballY - BALL_RADIUS < 0) {  
		ballX = WIDTH / 2.0f;
		ballY = HEIGHT / 2.0f;
		ballSpeedX = 2.0f;
		ballSpeedY = 2.0f;
	}
	if (ballY + BALL_RADIUS > HEIGHT) {
		ballX = WIDTH / 2.0f;
		ballY = HEIGHT / 2.0f;
		ballSpeedX = 2.0f;
		ballSpeedY = -2.0f;
	}

	glutPostRedisplay();
	glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Test");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutTimerFunc(0, update, 0);

	glutMainLoop();
}

