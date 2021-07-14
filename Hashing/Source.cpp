#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<time.h>


int hashit(int key, int choice);
int hf_division(int key);
int hf_midsquare(int key);
int hf_folding(int key);


#define table_size 8
#define PRIME 7
int cell_values[8] = { 150,250,350,450,550,650,750,850 };
int hash_table[8];
int translate_points[8][2] = { {1150,770},{1150,670}, {1150,570}, {1150,470}, {1150,370},
	{1150,270},{1150,170},{1150,70} };
int ll_values[8][8] = { NULL }, null_position[table_size] = { 0 };;

int type = 0, fill_y1 = 0, fill_y2 = 0;
void draw();

void delay(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock())
		;
}




void hashfunbox()
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(350, 630);
	glVertex2i(550, 630);
	glVertex2i(550, 730);
	glVertex2i(350, 730);
	glEnd();
	char s[] = "Hash function";
	glRasterPos3f(380, 680, 0);
	for (int i = 0; s[i]; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}
struct node
{
	int data;
	struct node* next;
};

struct node* chain[table_size];

void ll_init()
{
	int i;
	for (i = 0; i < table_size; i++)
		chain[i] = NULL;
}

void insert(int value)
{
	//create a newnode with value
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = value;
	newNode->next = NULL;

	//calculate hash key
	int key = value % table_size;

	//check if chain[key] is empty
	if (chain[key] == NULL)
		chain[key] = newNode;
	//collision
	else
	{
		//add the node at the end of chain[key].
		struct node* temp = chain[key];
		while (temp->next)
		{
			temp = temp->next;
		}

		temp->next = newNode;
	}
}



void cell_fill(int cell)
{
	//printf("\nInside fun");
	glRecti(1300, 900 - (cell * 100 + 50), 1400, 900 - (cell * 100 + 150));
	glutSwapBuffers();
	delay(1000);
}
char status_text[300];
void status()
{
	char heading[30] = "Algorithm explanation";

	int y = 400;
	glBegin(GL_LINE_LOOP);	//table
	glVertex2i(30, 100);
	glVertex2i(600, 100);
	glVertex2i(600, 500);
	glVertex2i(30, 500);
	glEnd();
	glRasterPos3f(200, 450, 0);
	for (int i = 0; heading[i]; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading[i]);
	glRasterPos3f(50, y, 0);
	for (int i = 0; status_text[i]; i++)
	{
		if (status_text[i] == '\n')
		{
			y -= 40;
			glRasterPos3f(50, y, 0);
		}
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, status_text[i]);
	}
}


void table_filler()
{
	char s[20];

	int x = 1335, y = 800;
	for (int i = 0; i < 8; i++) {
		sprintf(s, "%d", hash_table[i]);
		glRasterPos3f(x, y, 0);
		for (int i = 0; s[i]; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		y -= 100;

	}

}
void table() {
	int y1_table_line = 150, i;
	glBegin(GL_LINE_LOOP);	//table
	glVertex2i(1300, 50);
	glVertex2i(1400, 50);
	glVertex2i(1400, 850);
	glVertex2i(1300, 850);
	glEnd();

	for (i = 0; i < 7; i++) {		//cell creator
		glBegin(GL_LINES);
		glVertex2i(1300, y1_table_line);
		glVertex2i(1400, y1_table_line);
		glEnd();
		y1_table_line += 100;
	}

}

void ll_box()
{
	int x = 1450, y = 50;
	ll_values[0][0] = 2;
	ll_values[0][1] = 3;
	for (int i = 0; i < 8; i++)
	{
		y = 50 + i * 100;
		for (int j = 0; j < 8; j++)
		{
			if (ll_values[i][j] == NULL)
			{
				break;
			}
			glBegin(GL_LINE_LOOP);	//table
			glVertex2i(x, y);
			glVertex2i(x + 50, y + 100);
			glVertex2i(x + 50, y + 100);
			glVertex2i(x, y);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(x + 50, y + 50);
			glVertex2i(x + 75, y + 50);
			glEnd();
		}
	}
}
void ll_table()
{
	int y1_table_line = 150, i, links = 100;


	//glClear(GL_COLOR_BUFFER_BIT);


	glBegin(GL_LINE_LOOP);	//table
	glVertex2i(1000, 50);
	glVertex2i(1100, 50);
	glVertex2i(1100, 850);
	glVertex2i(1000, 850);
	glEnd();

	for (i = 0; i < 7; i++) {		//cell creator
		glBegin(GL_LINES);
		glVertex2i(1000, y1_table_line);
		glVertex2i(1100, y1_table_line);
		glEnd();


		glBegin(GL_LINES);			//draw links
		glVertex2i(1100, links);
		glVertex2i(1150, links);
		glEnd();


		//glFlush();
		links += 100;
		y1_table_line += 100;

	}
	glBegin(GL_LINES);// final link
	glVertex2i(1100, links);
	glVertex2i(1150, links);
	glEnd();

}
void drawbox(float x, float y, int element)
{
	char s[20];
	glPointSize(2.0);
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 100, y);
	glVertex2f(x + 100, y + 55);
	glVertex2f(x, y + 55);
	glEnd();
	sprintf(s, "%d", element);
	glRasterPos3f(x + 50, y + 20, 0);
	for (int i = 0; s[i]; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}

void draw_null()
{
	char s[7] = "Null";
	for (int i = 0; i < table_size; i++)
		null_position[i] = { 0 };
	for (int i = 0; i < table_size; i++)
	{
		struct node* temp = chain[i];
		while (temp)
		{
			null_position[i] += 1;

			temp = temp->next;
		}
	}
	for (int j = 0; j < table_size; j++)
	{
		glRasterPos3f(1150 + 150 * null_position[j], translate_points[j][1] + 21, 0);
		for (int i = 0; s[i]; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		}
	}
}


void draw_node()
{
	int xpos;
	for (int i = 0; i < table_size; i++)
	{
		xpos = 0;
		char s[20];
		struct node* temp = chain[i];
		while (temp)
		{

			glBegin(GL_LINE_LOOP);
			glVertex2f(1150 + 150 * xpos, translate_points[i][1]);
			glVertex2f((1150 + 150 * xpos) + 100, translate_points[i][1]);
			glVertex2f((1150 + 150 * xpos) + 100, translate_points[i][1] + 55);
			glVertex2f(1150 + 150 * xpos, translate_points[i][1] + 55);
			glEnd();

			glBegin(GL_LINES);// final link
			glVertex2i((1150 + 150 * xpos) + 100, translate_points[i][1] + 25);
			glVertex2i((1150 + 150 * xpos) + 150, translate_points[i][1] + 25);
			glEnd();


			sprintf(s, "%d", temp->data);
			glRasterPos3f((1150 + 150 * xpos) + 25, translate_points[i][1] + 25, 0);
			for (int i = 0; s[i]; i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
			}

			/*if (xpos == 0) {
				fill_y1 = 310;
				fill_y2 = 370;
				draw();
				delay(1000);
				glFlush();
			}
			else {
				fill_y1 = 150;
				fill_y2 = 250;
				draw();
				glFlush();
			}*/
			temp = temp->next;
			xpos += 1;
		}
	}
}
void display_string();
void inputbox() {
	char s[] = "Input";
	glRasterPos3f(65, 720, 0);
	for (int i = 0; s[i]; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	glBegin(GL_LINE_LOOP);
	glVertex2i(25, 640);
	glVertex2i(150, 640);
	glVertex2i(150, 710);
	glVertex2i(25, 710);
	glEnd();
	display_string();
}
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (type == 2)
	{
		ll_table();
		draw_null();
		draw_node();
		hashfunbox();
		inputbox();
	}
	else
	{
		table();
		table_filler();
		hashfunbox();
		inputbox();
	}
	status();

	/*glBegin(GL_LINE_LOOP);
	glVertex2i(40, fill_y1);
	glVertex2i(550, fill_y1);
	glVertex2i(550, fill_y2);
	glVertex2i(40, fill_y2);
	glEnd();*/
}

void movebox(int x1, int y1, int x2, int y2, int element, int ll_flag = 0)
{
	float x = x1, y = y1; //600 450 1150 570
	if (y2 > y1)
	{
		while (x2 > x || y2 > y)
		{

			draw();
			drawbox(x, y, element);
			glutSwapBuffers();
			if (x < x2)
				x += 1.5;//2.5
			if (y < y2)
				y += 1.5;
			//printf("%f\t%f\n", x, y);
			delay(10);
		}

	}
	else {
		while (x2 > x || y > y2)
		{
			draw();
			drawbox(x, y, element);
			glutSwapBuffers();
			if (x < x2)
				x += 1.5;
			if (y > y2)
				y -= 1.5;
			delay(10);
		}
		//draw(280, 310);
	}
}


void backward_movebox(int x1, int y1, int element)
{
	float x = x1, y = y1;
	while (x > 300 || y < 650)
	{

		draw();
		drawbox(x, y, element);
		glutSwapBuffers();
		if (x > 300)
			x -= 2.5;
		if (y < 650)
			y += 2.5;
		delay(10);
	}
}

int dh_hash1(int key)
{
	return (key % table_size);
}

// function to calculate second hash
int dh_hash2(int key)
{
	return (PRIME - (key % PRIME));
}

void display();

int state = 0;
void hash_option(int option)
{
	if (option == 1)
		type = 1;
	if (option == 2) {
		ll_table();
		ll_init();
		type = 2;
	}
	if (option == 3)
		type = 3;
	state = 0;
	display();
}

int  n, choice = 1, execDisplay = 0, insert_key = 0;
char buffer[128];
void display()
{
	int temp_index, temp_index1;
	if (state == 0) {
		int  i = 0, index;
		if (type == 1) {
			draw();
			printf("\before exec\n");
			if (execDisplay == 1) {

				strcat(status_text, "Hash technique: Linear probing");
				index = hashit(insert_key, choice);

				strcat(status_text, "\nHashing the key");
				movebox(150, 645, 500, 645, insert_key);

				sprintf(buffer, "\nIndex obtained by hashing: %d", index);
				strcat(status_text, buffer);

				strcat(status_text, "\nCheck index is empty");
				movebox(500, 645, translate_points[index][0], translate_points[index][1], index);


				if (hash_table[index] == NULL)
				{

					hash_table[index] = insert_key;
					strcat(status_text, "\nPosition is empty. Element placed");
					sprintf(buffer, "\nElement Placed successfully: %d", index);
					strcat(status_text, buffer);



					cell_fill(index);
					draw();
					glutSwapBuffers();
				}
				else
				{
					strcat(status_text, "\nIndex already filled. Probing linearly");
					//draw();
					//glutSwapBuffers();
					delay(1000);

					temp_index = index;
					temp_index1 = index;
					while (1)
					{
						if (index >= 7)
						{
							temp_index1 = index;
							index = 0;
							movebox(translate_points[temp_index1][0], translate_points[temp_index1][1], translate_points[index][0], translate_points[index][1], insert_key);
							delay(1000);
						}
						else
						{
							temp_index1 = index;
							index += 1;
							movebox(translate_points[temp_index1][0], translate_points[temp_index1][1], translate_points[index][0], translate_points[index][1], insert_key);
							delay(1000);
						}
						if (hash_table[index] == NULL)
						{
							sprintf(buffer, "\nEmpty index found by linear probe: %d", index);
							strcat(status_text, buffer);
							//movebox(translate_points[temp_index][0], translate_points[temp_index][1], translate_points[index][0], translate_points[index][1], insert_key);


							sprintf(buffer, "\nElement Placed successfully: %d", index);
							strcat(status_text, buffer);
							cell_fill(index);
							hash_table[index] = insert_key;
							draw();
							glutSwapBuffers();
							delay(100);

							break;
						}
						if (index == temp_index)
						{
							strcat(status_text, "\nHash table. Exiting");
							break;
						}
					}
				}
				printf("%s", status_text);
				strcpy(status_text, "");
				i += 1;
			}
		}
		if (type == 2)
		{

			draw();
			strcat(status_text, "Hash technique: Chaining");
			if (execDisplay == 1)
			{
				strcat(status_text, "\nHashing the key");
				movebox(150, 645, 500, 645, insert_key);

				index = hashit(insert_key, choice);

				sprintf(buffer, "\nIndex obtained by hashing: %d", index);
				strcat(status_text, buffer);

				movebox(500, 645, translate_points[index][0] - 300, translate_points[index][1], index, 1);
				
				strcat(status_text, "\nPlaceing the key");
				movebox(translate_points[index][0], translate_points[index][1], (1151 + 100 * null_position[i]), translate_points[index][1], insert_key, 1);
				insert(insert_key);
				//delay(1000);
				//glClear(GL_COLOR_BUFFER_BIT);
				//fill_y1 = 100;
				//fill_y2 = 60;
				draw();
				//delay(1000);
				glutSwapBuffers();
				strcpy(status_text, "");
			}
		}
		if (type == 3) {
			draw();
			strcat(status_text, "Hash technique: Double hashing");
			if (execDisplay == 1)
			{
				movebox(150, 645, 500, 645, insert_key);
				index = dh_hash1(insert_key);
				sprintf(buffer, "\nIndex obtained by hashing: %d", index);
				strcat(status_text, buffer);

				strcat(status_text, "\nCheck index is empty");
				movebox(500, 645, translate_points[index][0], translate_points[index][1], index);
				cell_fill(index);
				glutSwapBuffers();
				delay(1000);
				

				if (hash_table[index] != NULL) {
					int index2 = dh_hash2(insert_key), newIndex=index;
					int j = 1;
					while (1) {
						//movebox(translate_points[index][0], translate_points[index][1], 50, 625, index);
						backward_movebox(translate_points[newIndex][0], translate_points[newIndex][1], index);

						strcat(status_text, "\nPerforming hashing again");
						newIndex = (index + j * index2) % table_size;

						movebox(50, 645, 500, 645, insert_key);
						sprintf(buffer, "\nIndex obtained by double hashing: %d", newIndex);
						strcat(status_text, buffer);
						movebox(500, 645, translate_points[newIndex][0], translate_points[newIndex][1], newIndex);
						cell_fill(newIndex);
						glutSwapBuffers();
						delay(1000);
						if (hash_table[newIndex] == NULL) {
							sprintf(buffer, "\nEmpty index found by Double hashin: %d", newIndex);
							strcat(status_text, buffer);
							hash_table[newIndex] = insert_key;
							cell_fill(newIndex);
							glutSwapBuffers();
							delay(1000);
							break;
						}
						j++;
					}
				}
				else
				{
					hash_table[index] = insert_key;
					sprintf(buffer, "\nEmpty index found by linear probe: %d", index);
					strcat(status_text, buffer);
					
					
					
					
				}
				draw();
				glutSwapBuffers();
				strcpy(status_text, "");
			}
		}
	}
	state += 1;
}

char bufferO[10] = "";
void display_string() {
	int wide = 0;
	for (int i = 0; bufferO[i]; i++) {
		glRasterPos3f(wide + 50, 670, 0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, bufferO[i]);
		wide += 12;
	}
}
void keyboard(unsigned char key, int x, int y) {
	char s[3];
	s[0] = key;
	s[1] = '\0';

	if (!isdigit(key));
	else if (type != 0) {
		strcat(bufferO, s);
		display_string();
		draw();
		glFlush();
	}
	if (key == 13) {

		insert_key = atoi(bufferO);
		strcpy(bufferO, "");
		execDisplay = 1;
		state = 0;
		display();
	}
}


void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glClearColor(2.0, 2.0, 2.0, 4.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, glutGet(GLUT_SCREEN_WIDTH), 0.0, glutGet(GLUT_SCREEN_HEIGHT));
	glClear(GL_COLOR_BUFFER_BIT);
	if (type != 0) {
		draw();
		glutSwapBuffers();
	}
}
///////////////////



int hf_division(int key)
{
	return key % table_size;
}

int hf_midsquare(int key) {
	int digits = (int)log10(key) + 1;
	return ((int)(key / pow(10, digits / 2)) % 10);
}

int hf_folding(int key) {
	int sum = 0, m;
	while (key > 0)
	{
		m = key % 10;
		sum = sum + m;
		key = key / 10;
	}
	return sum % table_size;
}


int hashit(int key, int choice) {
	int index;
	switch (choice)
	{
	case 1:
		index = hf_division(key);
		break;
	case 2:
		index = hf_midsquare(key);
		break;
	case 3:
		index = hf_folding(key);
		break;
	default:
		index = hf_division(key);
		break;
	}
	return index;

}

void main(int argc, char** argv)
{

	for (int i = 0; i < 7; i++)
	{
		hash_table[i] = NULL;
	}

	//printf("Choose the hashing function\n1.Division method\n2.Mid square method\n3.Digit folding : ");
	//scanf("%d", &choice);
	choice = 1;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Hashing");
	//myInit();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutCreateMenu(hash_option);
	glutAddMenuEntry("Linear Probing", 1);
	glutAddMenuEntry("Chaining", 2);
	glutAddMenuEntry("Double hashing", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

}