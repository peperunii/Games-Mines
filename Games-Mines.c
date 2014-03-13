#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

/*
	HideCursor function
*/
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

/*
    CheckForRealSolution function
*/
int CheckForRealSolution(char *HiddenMinesArray, char *MinesArray, int MineWindowSize, int MineCounter, int NumberOfMines)
{
	int i, j;
	int realMines = 0;
	if (MineCounter == NumberOfMines)
	{
		for (i = 0; i < 2 * MineWindowSize + 1; i++)
		{
			for (j = 0; j < 2 * MineWindowSize + 1; j++)
			{
				if (MinesArray[i * (2 * MineWindowSize + 1) + j] == '+')
				{
					if (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] == '*')
						realMines+=1;
				}
			}
		}
	}
	return realMines;
}

/*
	CreateGRID function
*/
void CreateGRID(char * MinesArray, int MineWindowSize)
{
	int i, j;
	for (i = 0; i < 2 * MineWindowSize + 1; i++)
	{
		if (i % 2 == 0)
		{
			for (j = 0; j < 2 * MineWindowSize + 1; j++)
			{
				MinesArray[(i * (2 * MineWindowSize + 1)) + j] = '-';
			}
		}
		else
		{
			for (j = 0; j < 2 * MineWindowSize + 1; j++)
			{
				if (j % 2 == 0)  { MinesArray[i * (2 * MineWindowSize + 1) + j] = 124; }
				else
				{
					//MinesArray[i * (2*MineWindowSize + 1) + j] = 32;
				}
			}
		}
	}
}
/*
	initializeArrays function
*/
void InitialiseArrays(char *HiddenMinesArray, char *MinesArray, int MineWindowSize)
{
	int i, j;

	for (i = 0; i < 7 * MineWindowSize *MineWindowSize; i++) MinesArray[i] = 32;
	for (i = 0; i < 2 * MineWindowSize + 1; i++)
	{
		if (i % 2 == 0)
		{
			for (j = 0; j < 2 * MineWindowSize + 1; j++)
			{
				MinesArray[(i * (2 * MineWindowSize + 1)) + j] = '-';
			}
		}
		else
		{
			for (j = 0; j < 2 * MineWindowSize + 1; j++)
			{
				if (j % 2 == 0)  { MinesArray[i * (2 * MineWindowSize + 1) + j] = 124; }
				else
				{
					MinesArray[i * (2 * MineWindowSize + 1) + j] = 32;
				}
			}
		}
	}
	for (i = 0; i < 7 * MineWindowSize *MineWindowSize; i++) HiddenMinesArray[i] = 0;

}

/*
	PlaceMines function
*/
void PlaceMines(char *HiddenMinesArray, char *MinesArray, int MineWindowSize, int NumberOfMines)
{
	int i, j;
	int MineCoordX = 0;
	int MineCoordY = 0;
	for (i = 0; i < NumberOfMines; i++)
	{
		while (1)
		{
			MineCoordX = 1 + rand() % (2 * MineWindowSize - 1);
			MineCoordY = 1 + rand() % (2 * MineWindowSize - 1);
			if (MinesArray[MineCoordY * (2 * MineWindowSize + 1) + MineCoordX] == 32) // empty space
			{
				if (HiddenMinesArray[MineCoordY * (2 * MineWindowSize + 1) + MineCoordX] != '*')
				{
					HiddenMinesArray[MineCoordY * (2 * MineWindowSize + 1) + MineCoordX] = '*';
					break;
				}
			}
		}
	}
}
/*
	PlaceNumbersAroundMines function
*/
void PlaceNumbersAroundMines(char *HiddenMinesArray, char *MinesArray, int MineWindowSize)
{
	int i, j = 0;
	int MinesAround = 0;
	for (i = 0; i < 2 * MineWindowSize + 1; i++)
	{
		if (i % 2 == 0) continue;
		for (j = 0; j < 2 * MineWindowSize + 1; j++)
		{
			MinesAround = 0;
			if (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] != '*')
			{
				if (((MinesArray[i * (2 * MineWindowSize + 1) + j]) != '-') && ((MinesArray[i * (2 * MineWindowSize + 1) + j]) != '|'))
				{
					//check surrounded area for mines
					/* check if there are squares on the left */
					if ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2)
					{
						if (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] == '*') MinesAround++;
					}
					/* check if there are squares on the right */
					if ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1))
					{
						if (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] == '*') MinesAround++;
					}
					/* check if there are squares up */
					if ((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1)))
					{
						if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] == '*') MinesAround++;
					}
					/* check if there are squares down */
					if ((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2)))
					{
						if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] == '*') MinesAround++;
					}
					/* diagonals */

					/* up-left */
					if (((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2))
					{
						if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] == '*') MinesAround++;
					}
					/* up right */
					if (((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1)))
					{
						if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] == '*') MinesAround++;
					}
					/* down - left*/
					if (((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2))
					{
						if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] == '*') MinesAround++;
					}
					/* down right */
					if (((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1)))
					{
						if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] == '*') MinesAround++;
					}

					switch (MinesAround)
					{
						case 0: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = '.';  //0
							break;
						case 1: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 49;  // .
							break;
						case 2: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 50;  // .
							break;
						case 3: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 51;  // .
							break;
						case 4: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 52;  // .
							break;
						case 5: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 53;  // .
							break;
						case 6: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 54;  // .
							break;  
						case 7: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 55;  // .
							break;
						case 8: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 56;  // .
							break;
						case 9: HiddenMinesArray[i * (2 * MineWindowSize + 1) + j] = 57;  // 9
							break;
					}
				}
			}
		}
	}
}
/*
	openNearbySquares function
*/
void openNearbySquares(char *HiddenMinesArray, char *MinesArray, int i, int j, int MineWindowSize, int* Death, int skipHalfFunction, int *prcessedRecurseArray)
{
	int k = 0;
	int MinesAround = 0;
	int weHaveAMine[8];// = { 0, 0, 0, 0, 0, 0, 0, 0 };
	for (k = 0; k < 8; k++) weHaveAMine[k] = 0;
	/* count marked mines around*/
	//check surrounded area for mines

	if (skipHalfFunction) { skipHalfFunction++;  goto skipHalf; }

	/* check if there are squares on the left */
	if ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2)
	{
		if (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] == '*')  
		{
			weHaveAMine[0] = 1;
		}
		if ((MinesArray[i * (2 * MineWindowSize + 1) + j - 2] == '+'))
		{
			MinesAround++;
		}
	}
	/* check if there are squares on the right */
	if ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1)) 
	{
		if (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] == '*')
		{
			weHaveAMine[1] = 1;
		}
		if ((MinesArray[i * (2 * MineWindowSize + 1) + j + 2] == '+'))
		{
			MinesAround++;
		}
	}
	/* check if there are squares up */
	if ((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1)))
	{
		if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] == '*') 
		{
			weHaveAMine[2] = 1;
		}
		if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] == '+'))
		{
			MinesAround++;
		}
	}
	/* check if there are squares down */
	if ((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2)))
	{
		if ((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] == '*') && (MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] == '+'))
		{
			weHaveAMine[3] = 1;
		}
		if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] == '+'))
		{
			MinesAround++;
		}
	}
	/* diagonals */

	/* up-left */
	if (((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2))
	{
		if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] == '*') 
		{
			weHaveAMine[4] = 1;
		}
		if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] == '+'))
		{
			MinesAround++;
		}
	}
	/* up right */
	if (((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1)))
	{
		if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] == '*') 
		{
			weHaveAMine[5] = 1;
		}
		if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] == '+'))
		{
			MinesAround++;
		}
	}
	/* down - left*/
	if (((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2))
	{
		if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] == '*')  
		{
			weHaveAMine[6] = 1;
		}
		if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] == '+'))
		{
			MinesAround++;
		}
	}
	/* down right */
	if (((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1)))
	{
		if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] == '*')
		{
			weHaveAMine[7] = 1;
		}
		if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] == '+'))
		{
			MinesAround++;
		}
	}

skipHalf:
	/* if the number in the square is equal to the number stored in MinesAround */
	if ((MinesAround == (MinesArray[(i * (2 * MineWindowSize + 1)) + j] - 48)) || ((MinesArray[(i * (2 * MineWindowSize + 1)) + j]) == '.'))
	{
		/* check if there are squares on the left */
		if ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2)
		{
			if ((HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] == '*') && (weHaveAMine[0] == 0))
			{
				*Death = 1; return;
			}
			if ((HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] != '*') && (weHaveAMine[0] == 1))
			{
				*Death = 1; return;
			}
			if (((HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] > '0') &&
				 (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] <= '9')) ||
				 (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] == '.'))
			{
				MinesArray[i * (2 * MineWindowSize + 1) + j - 2] = HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2];
			}
			/* Recursive call... to open all nearby squares when there is no number. just '.' */
			if (MinesArray[i * (2 * MineWindowSize + 1) + j - 2] == '.')
			{
				if (prcessedRecurseArray[((i - 1) / 2)*MineWindowSize + ((j - 1) / 2) - 1] == 0)
				{
					prcessedRecurseArray[((i - 1) / 2)*MineWindowSize + ((j - 1) / 2) - 1] = 1;
					openNearbySquares(HiddenMinesArray, MinesArray, i, j - 2, MineWindowSize, &Death, 1, prcessedRecurseArray);
				}
			}

		}
		//if (*Death) return;
		/* check if there are squares on the right */
		if ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1))
		{
			if ((HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] == '*') && (weHaveAMine[1] == 0))
			{
				*Death = 1; return;
			}
			if ((HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] != '*') && (weHaveAMine[1] == 1))
			{
				*Death = 1; return;
			}
			if (((HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] > '0') &&
				 (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] <= '9')) ||
				 (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] == '.'))
			{
				MinesArray[i * (2 * MineWindowSize + 1) + j + 2] = HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2];
			}
			/* Recursive call... to open all nearby squares when there is no number. just '.' */
			if (MinesArray[i * (2 * MineWindowSize + 1) + j + 2] == '.')
			{
				if (prcessedRecurseArray[((i - 1) / 2)*MineWindowSize + ((j - 1) / 2) + 1] == 0)
				{
					prcessedRecurseArray[((i - 1) / 2)*MineWindowSize + ((j - 1) / 2) + 1] = 1;
					openNearbySquares(HiddenMinesArray, MinesArray, i, j + 2, MineWindowSize, &Death, 1, prcessedRecurseArray);
				}
			}
		}
		//if (*Death) return;
		/* check if there are squares up */
		if ((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1)))
		{
			if ((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] == '*') && (weHaveAMine[2] == 0))
			{
				*Death = 1; return;
			}
			if ((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] != '*') && (weHaveAMine[2] == 1))
			{
				*Death = 1; return;
			}
			if (((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] > '0') &&
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] <= '9')) || 
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] == '.'))
			{
				MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] = HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)];
			}
			/* Recursive call... to open all nearby squares when there is no number. just '.' */
			if (MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] == '.')
			{
				if (prcessedRecurseArray[(((i - 1) / 2) - 1)*MineWindowSize + ((j - 1) / 2)] == 0)
				{
					prcessedRecurseArray[(((i - 1) / 2) - 1)*MineWindowSize + ((j - 1) / 2)] = 1;
					openNearbySquares(HiddenMinesArray, MinesArray, i - 2, j, MineWindowSize, &Death, 1, prcessedRecurseArray);
				}
			}
		}
		//if (*Death) return;
		/* check if there are squares down */
		if ((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2)))
		{
			if (MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] == '+') 
			{
				if ((weHaveAMine[3] == 0))
				{
					*Death = 1; return;
				}
			}
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] != '+') && (weHaveAMine[3] == 1))
			{
				*Death = 1; return;
			}
			if (((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] > '0') &&
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] <= '9')) ||
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] == '.'))
			{
				MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] = HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)];
			}
			/* Recursive call... to open all nearby squares when there is no number. just '.' */
			if (MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] == '.')
			{
				if (prcessedRecurseArray[(((i - 1) / 2) + 1)*MineWindowSize + ((j - 1) / 2)] == 0)
				{
					prcessedRecurseArray[(((i - 1) / 2) + 1)*MineWindowSize + ((j - 1) / 2)] = 1;
					openNearbySquares(HiddenMinesArray, MinesArray, i + 2, j, MineWindowSize, &Death, 1, prcessedRecurseArray);
				}
			}
		}
		/* diagonals */

		/* up-left */
		if (((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2))
		{
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] == '+') && (weHaveAMine[4] == 0))
			{
				*Death = 1; return;
			}
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] != '+') && (weHaveAMine[4] == 1))
			{
				*Death = 1; return;
			}
			if (((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] > '0') &&
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] <= '9')) ||
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] == '.'))
			{
				MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] = HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2];
			}
			/* Recursive call... to open all nearby squares when there is no number. just '.' */
			if (MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) - 2] == '.')
			{
				if (prcessedRecurseArray[(((i - 1) / 2) - 1)*MineWindowSize + ((j - 1) / 2) - 1] == 0)
				{
					prcessedRecurseArray[(((i - 1) / 2) - 1)*MineWindowSize + ((j - 1) / 2) - 1] = 1;
					openNearbySquares(HiddenMinesArray, MinesArray, i - 2, j - 2, MineWindowSize, &Death, 1, prcessedRecurseArray);
				}
			}
		}
		/* up right */
		if (((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1)))
		{
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] == '+') && (weHaveAMine[5] == 0))
			{
				*Death = 1; return;
			}
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] != '+') && (weHaveAMine[5] == 1))
			{
				*Death = 1; return;
			}
			if (((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] > '0') && 
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] <= '9')) || 
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] == '.'))
			{
				MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] = HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2];
			}
			/* Recursive call... to open all nearby squares when there is no number. just '.' */
			if (MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1) + 2] == '.')
			{
				if (prcessedRecurseArray[(((i - 1) / 2) - 1)*MineWindowSize + ((j - 1) / 2) + 1] == 0)
				{
					prcessedRecurseArray[(((i - 1) / 2) - 1)*MineWindowSize + ((j - 1) / 2) + 1] = 1;
					openNearbySquares(HiddenMinesArray, MinesArray, i - 2, j + 2, MineWindowSize, &Death, 1, prcessedRecurseArray);
				}
			}
		}
		/* down - left*/
		if (((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2))
		{
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] == '+') && (weHaveAMine[6] == 0))
			{
				*Death = 1; return;
			}
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] != '+') && (weHaveAMine[6] == 1))
			{
				*Death = 1; return;
			}
			if (((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] > '0') && 
				 (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] <= '9')) ||
				 ((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] == '.')))
			{
				MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] = HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2];
			}
			/* Recursive call... to open all nearby squares when there is no number. just '.' */
			if (MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) - 2] == '.')
			{
				if (prcessedRecurseArray[(((i - 1) / 2) + 1)*MineWindowSize + ((j - 1) / 2) - 1] == 0)
				{
					prcessedRecurseArray[(((i - 1) / 2) + 1)*MineWindowSize + ((j - 1) / 2) - 1] = 1;
					openNearbySquares(HiddenMinesArray, MinesArray, i + 2, j - 2, MineWindowSize, &Death, 1, prcessedRecurseArray);
				}
			}
		}
		/* down right */
		if (((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2))) && ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1)))
		{
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] == '+') && (weHaveAMine[7] == 0))
			{
				*Death = 1; return;
			}
			if ((MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] != '+') && (weHaveAMine[7] == 1))
			{
				*Death = 1; return;
			}
			if (((HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] > '0') &&
				(HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] <= '9')) ||
				(HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] == '.'))
			{
				MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] = HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2];
			}
			/* Recursive call... to open all nearby squares when there is no number. just '.' */
			if (MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1) + 2] == '.')
			{
				if (prcessedRecurseArray[(((i - 1) / 2) + 1)*MineWindowSize + ((j - 1) / 2) + 1] == 0)
				{
					prcessedRecurseArray[(((i - 1) / 2) + 1)*MineWindowSize + ((j - 1) / 2) + 1] = 1;
					openNearbySquares(HiddenMinesArray, MinesArray, i + 2, j + 2, MineWindowSize, &Death, 1, prcessedRecurseArray);
				}
			}
		}
	}
	if (skipHalfFunction) Death = 0;
	return;
}
/*
	FindEmptySpaces function
*/
int findEmptySpaces(char *HiddenMinesArray, char *MinesArray, int i, int j, int MineWindowSize)
{
	//check surrounded area for mines
	/* check if there are squares on the left */
	if ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) > 2)
	{
		if (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] == '0') 
		{
			//MinesAround++; 
			MinesArray[i * (2 * MineWindowSize + 1) + j - 2] = '.';
			HiddenMinesArray[i * (2 * MineWindowSize + 1) + j - 2] = '.';
			findEmptySpaces(HiddenMinesArray, MinesArray, i, j - 2, MineWindowSize);
		}
	}
	/* check if there are squares on the right */
	if ((i * (2 * MineWindowSize + 1) + j) % (2 * MineWindowSize + 1) < (2 * MineWindowSize - 1))
	{
		if (HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] == '0')
		{
			MinesArray[i * (2 * MineWindowSize + 1) + j + 2] = '.';
			HiddenMinesArray[i * (2 * MineWindowSize + 1) + j + 2] = '.';
			findEmptySpaces(HiddenMinesArray, MinesArray, i, j + 2, MineWindowSize);
		}
	}
	/* check if there are squares up */
	if ((i * (2 * MineWindowSize + 1) + j) > (3 * (2 * MineWindowSize + 1)))
	{
		if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] == '0')
		{
			MinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] = '.';
			HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) - 2 * (2 * MineWindowSize + 1)] = '.';
			findEmptySpaces(HiddenMinesArray, MinesArray, i, j - 2 * (2 * MineWindowSize + 1 ), MineWindowSize);
		}
	}
	/* check if there are squares down */
	if ((i * (2 * MineWindowSize + 1) + j) < ((2 * MineWindowSize + 1)*(2 * MineWindowSize - 2)))
	{
		if (HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] == '0')
		{
			MinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] = '.';
			HiddenMinesArray[(i * (2 * MineWindowSize + 1) + j) + 2 * (2 * MineWindowSize + 1)] = '.';
			findEmptySpaces(HiddenMinesArray, MinesArray, i, j + 2 * (2 * MineWindowSize + 1), MineWindowSize);
		}
	}
	
	/* No diagonals for zeros*/
	/* diagonals */

	return 0;
}

/*
Config file: config.cfg

Enable_H_button					1
Enable_I_button					1
Save_Records					1
Records_filename				RecordList.txt // Need to exist in the current working Dir
MinimumWindowSize				2
MaximumWindowSize				9
MinimumNumberOfMines			1
CheckForSolution_beforeEnter	1
hideKursor						1  // sugested value = 1
Dont_HIT_mines_withEnter		1
Show_nearestEmptySquaresMatrix  1  // works only with Enable_H_button = 1
*/
int main()
{
	FILE *fp_config = NULL;
	FILE *fp = NULL;
	int NUMBER_OF_CONFIG_ELEMENTS = 11;
	int ENABLE_H_BUTTON = 0;
	int ENABLE_I_BUTTON = 0;
	int SAVE_RECORDS = 0;
	int MINIMUM_WINDOW_SIZE = 2;
	int MAXIMUM_WINDOWS_SIZE = 9;
	int MINIMUM_NUMBER_OF_MINES = 1;
	int CHECK_FOR_REAL_SOLUTION_BEFORE_ENTER = 1;
	int HIDE_KURSOR = 1;
	int DONT_HIT_MINES_WITH_ENTER;
	int SHOW_NEAREST_EMPTY_SQUARES_MATRIX = 0;
	int x = 1;
	int y = 1;
	long size = 0;
	int hui = 0;
	int Win = 0;
	int pass = 0;
	char Key = 0;
	int Death = 0;
	int time_n = 0;
	int minuti = 0;
	int isSpace = 0;
	int isEnter = 0;
	int i, k, j = 0;
	int solution = 0;
	int realMines = 0;
	int BestResult = 0;
	int BestResult2 = 0;
	char MineSearchStringInFile[25];
	int userChoice = 0;
	int MineCoordX = 0;
	char unused[40];
	char recordList_fileName[35];
	char RecordListItems_strings[25] = "                         ";
	int  RecordListItems_times;
	int MineCoordY = 0;
	int MineCounter = 0;
	int CursorBlink = 0;
	int information = 0;
	int MinesAround = 0;
	int time_seconds = 0;
	int NumberOfMines = 0;
	int ClearSolution = 0;
	int namereno = 0;
	int FirstClickSave = 0;
	int NumberOfDigits = 0;
	int MineWindowSize = 10;
	int ClearInformation = 0;
	char anotherUselessString[25];
	char NewGameChoice = ' ';
	char *MinesArray = NULL;
	char infos[12][75] = { "    Welcome to MINES    ", " - Press Enter to reveal a square", " - Enter twice to reveal squares around", " - Press Space to mark a mine", " - First click is always safe !", " - Win the game marking all mines", "  Legend: ", "  + Marked mine", "  - Cursor position", "  (1-9) Number of mines around", "  . no mines around" };
	char *HiddenMinesArray = NULL;
	int anotherStupidFlagusedForMinutes = 0;
	int *prcessedRecurseArray = NULL;

	COORD pos = { x, y };
	COORD pos_cursor = { x, y };
	COORD pos_solution = { x, y };
	COORD pos_info = { x, y };
	COORD pos_Addinfo = { x, y };

	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE cursor = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE info = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE solut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE add_info = GetStdHandle(STD_OUTPUT_HANDLE);

	fp_config = fopen("config.cfg", "rt");
	if (fp_config == NULL) 
	{ 
		printf("Cannot find config file config.cfg\nThe program will now exit...\n"); 
		_getch(); 
		return 0;
	}

	for (i = 0; i < NUMBER_OF_CONFIG_ELEMENTS; i++)
	{
		if (i == 0) fscanf(fp_config, "%s%d", unused, &ENABLE_H_BUTTON);
		if (i == 1) fscanf(fp_config, "%s%d", unused, &ENABLE_I_BUTTON);
		if (i == 2) fscanf(fp_config, "%s%d", unused, &SAVE_RECORDS);
		if (i == 3) fscanf(fp_config, "%s%s", unused, recordList_fileName);
		if (i == 4) fscanf(fp_config, "%s%d", unused, &MINIMUM_WINDOW_SIZE);
		if (i == 5) fscanf(fp_config, "%s%d", unused, &MAXIMUM_WINDOWS_SIZE);
		if (i == 6) fscanf(fp_config, "%s%d", unused, &MINIMUM_NUMBER_OF_MINES);
		if (i == 7) fscanf(fp_config, "%s%d", unused, &CHECK_FOR_REAL_SOLUTION_BEFORE_ENTER);
		if (i == 8) fscanf(fp_config, "%s%d", unused, &HIDE_KURSOR);
		if (i == 9) fscanf(fp_config, "%s%d", unused, &DONT_HIT_MINES_WITH_ENTER);
		if (i == 10) fscanf(fp_config, "%s%d", unused, &SHOW_NEAREST_EMPTY_SQUARES_MATRIX);
	}
	fclose(fp_config);

	if (SAVE_RECORDS)
	{
		fp = fopen(recordList_fileName, "rt"); // Just check existance of the file
		if (fp == NULL)
		{
			printf("Cannot open Records file. Continue without saving fastest times?\n1: yes\n2: No\n");
			scanf("%d", &userChoice);
			if (userChoice == 2)
			{
				printf("Bye bye");
				_getch();
				return 0;
			}
		}
		fclose(fp);
	}

	while (1)
	{
		i = 0;
		j = 0;
		k = 0;
		Key = 0;
		time_n = 0;
		time_seconds = 0;
		MineCoordX = 0;
		MineCoordY = 0;
		x = 1;
		solution = 0;
		information = 0;
		ClearSolution = 0;
		ClearInformation = 0;
		y = 1;
		isSpace = 0;
		pass = 0;
		isEnter = 0;
		Death = 0;
		Win = 0;
		minuti = 0;
		NumberOfMines = 0;
		MineCounter = 0;
		MinesArray = NULL;
		int iterationNumber;
		HiddenMinesArray = NULL;
		NewGameChoice = ' ';
		realMines = 0;
		MinesAround = 0;
		*MineSearchStringInFile = "                              ";
		output = GetStdHandle(STD_OUTPUT_HANDLE);
		cursor = GetStdHandle(STD_OUTPUT_HANDLE);
		solut  = GetStdHandle(STD_OUTPUT_HANDLE);
		anotherStupidFlagusedForMinutes = 0;

		srand(time(NULL));

		do{
			system("cls");
			fflush(stdin);
			printf("Enter the size of the area: ");
			scanf("%d", &MineWindowSize);
			printf("\n");
			if (MineWindowSize >= MINIMUM_WINDOW_SIZE && MineWindowSize <= MAXIMUM_WINDOWS_SIZE) break;
		} while (1);

		prcessedRecurseArray = (int*)malloc(MineWindowSize*MineWindowSize* sizeof(int));
		if (prcessedRecurseArray == NULL){ printf("not enough memory\n"); return 0; }
		for (i = 0; i < MineWindowSize*MineWindowSize; i++)
		{
			prcessedRecurseArray[i] = 0;
		}

		while (1)
		{
			fflush(stdin);
			printf("Enter Number of mines\nMines = ");
			scanf("%d", &NumberOfMines);
			printf("\n");
			if ((NumberOfMines >= MINIMUM_NUMBER_OF_MINES) && (NumberOfMines < MineWindowSize * MineWindowSize - 1)) break;
		}
		
		namereno = 0;
		BestResult = 999;
		if (SAVE_RECORDS)
		{
			fp = fopen("RecordList.txt", "rt");
			if (fp != NULL)
			{
				sprintf(MineSearchStringInFile, "%dx%d-%dmines", MineWindowSize, MineWindowSize, NumberOfMines);
				for (i = 0; i < 25; i++) // read every line from file (first 25)
				{
					fscanf(fp, "%s %d\n", RecordListItems_strings, &BestResult);  //%[^;] instead of %s 
					if (!(strcmp(RecordListItems_strings, MineSearchStringInFile)))
					{
						namereno = 1;
						break;
					}
				}
				if (!namereno)
				{
					fclose(fp);
					fp = fopen("RecordList.txt", "a");
					if (fp != NULL)
					{
						fprintf(fp, "%s %d\n", MineSearchStringInFile, 999);
					}
					fclose(fp);
					BestResult = 999;
				}
			}
		}
		if (fp != NULL) fclose(fp);
		
		if(HIDE_KURSOR) 
			hidecursor();

		MinesArray = malloc(7 * MineWindowSize *MineWindowSize *sizeof(char));
		HiddenMinesArray = malloc(7 * MineWindowSize *MineWindowSize *sizeof(char));
hui:
		/* init the two arrays */
		InitialiseArrays(HiddenMinesArray, MinesArray, MineWindowSize);
		
		/* put mines in the  HIDDENminesArray */
		PlaceMines(HiddenMinesArray, MinesArray, MineWindowSize, NumberOfMines);

		/* Put numbers around the mines in HIDDENminesArray */
		PlaceNumbersAroundMines(HiddenMinesArray, MinesArray, MineWindowSize);
		
		system("cls");
		pos.X = 0;
		pos.Y = 0;
		k = 0;
		MineCounter = 0;
		minuti = 0;
		FirstClickSave = 0;
		time_seconds = 0;
		SetConsoleCursorPosition(output, pos);
		Death = 0;
		iterationNumber = 0;
		while (1)
		{
			isEnter = 0;
			isSpace = 0;
			
			realMines = 0;
			if (_kbhit())
			{
				switch (_getch())
				{
				case 72:
					if(y -2 > 0)
						y -= 2;
					break;
				case 80:
					if(y+2 < (2*MineWindowSize +1))
						y += 2;
					break;
				case 75:
					if (x - 2 > 0)
						x -= 2;
					break;
				case 77:
					if (x + 2 < (2 * MineWindowSize + 1))
						x += 2;
					break;
				case 13:  //enter
					isEnter = 1;
					break;
				case 32: // space
					isSpace = 1;
					break;
				case 'h':
					if (ENABLE_H_BUTTON)
					{
						if (solution == 0)
						{
							solution = 1;
							ClearSolution = 0;
						}
						else ClearSolution = 1;
					}
					break;
				case 'i':
					if (ENABLE_I_BUTTON)
					{
						if (information == 0)
						{
							information = 1;
							ClearInformation = 0;
						}
						else ClearInformation = 1;
					}
					break;
				}
			}
			
			/* create the table for the user interface */
			CreateGRID(MinesArray, MineWindowSize);

			if (isEnter)
			{
				if (DONT_HIT_MINES_WITH_ENTER) if(MinesArray[(y * (2 * MineWindowSize + 1)) + x] == '+') goto isNotEnter;
				iterationNumber++;
				/* if any other number is hitted and there are marked mines with number equal to  the number in the square then open all nearby squares */
				if (((MinesArray[(y * (2 * MineWindowSize + 1)) + x] > '0') && (MinesArray[(y * (2 * MineWindowSize + 1)) + x] <= '9')) || (MinesArray[(y * (2 * MineWindowSize + 1)) + x] == '.'))
				{
					openNearbySquares(HiddenMinesArray, MinesArray, y, x, MineWindowSize, &Death, 0, prcessedRecurseArray);
				}
				if (Death) break;
				MinesArray[(y * (2 * MineWindowSize + 1)) + x] = HiddenMinesArray[(y * (2 * MineWindowSize + 1)) + x];
				if (MinesArray[(y * (2 * MineWindowSize + 1)) + x] == '*') {
					Death = 1; 
					FirstClickSave = 1;
				}			
			}

isNotEnter:
			if (FirstClickSave)
			{ 
				if (iterationNumber == 1)
				goto hui;
			}
			if (isSpace)
			{
				if (MinesArray[(y * (2 * MineWindowSize + 1)) + x] == '+')
				{
					MinesArray[(y * (2 * MineWindowSize + 1)) + x] = 32;
					MineCounter--;
				}
				else
				{
					if (MinesArray[(y * (2 * MineWindowSize + 1)) + x] == 32)
					{
						MinesArray[(y * (2 * MineWindowSize + 1)) + x] = '+';
						MineCounter++;
					}
				}
			}
			for (i = 0; i < 2 * MineWindowSize + 1; i++)
			{
				for (j = 0; j < 2 * MineWindowSize + 1; j++)
				{
					printf("%c", MinesArray[i * (2 * MineWindowSize + 1) + j]);
				}
				printf("\n");
			}

			/* Check if selected mines are real mines - winning solution */
			if (iterationNumber != 0)
			{
				if (isEnter || CHECK_FOR_REAL_SOLUTION_BEFORE_ENTER)
				{
					realMines = CheckForRealSolution(HiddenMinesArray, MinesArray, MineWindowSize, MineCounter, NumberOfMines);
					if (realMines == NumberOfMines) Win = 1;
				}
			}
			pos_cursor.X = x;
			pos_cursor.Y = y;
			SetConsoleCursorPosition(cursor, pos_cursor);
			if (!isEnter && !isSpace && MinesArray[(y * (2 * MineWindowSize + 1)) + x] == 32)
			{
				printf("-");
				k++;
			}
			else
			{
				if (CursorBlink)
				{
					printf("-");
					k++;
					CursorBlink = 0;
				}
				else CursorBlink = 1;
			}

			time_n++;
			if (time_n % 5 == 0) time_seconds++; // depend on the sleep function // Sleep(200);
			if ((time_seconds % 60 == 0) && (time_seconds > 0))
			{ 
				minuti++; 
				time_seconds = 0; 
				anotherStupidFlagusedForMinutes = 1; 
			}

			pos_info.X = 0;
			pos_info.Y = 2 * MineWindowSize + 2;
			SetConsoleCursorPosition(info, pos_info);
			printf("Mines left: %d  \n", NumberOfMines - MineCounter);
			
			if (anotherStupidFlagusedForMinutes == 1) 
			{
				anotherStupidFlagusedForMinutes = 0; 
				pos_info.X = 0;
				pos_info.Y = 2 * MineWindowSize + 3;
				SetConsoleCursorPosition(info, pos_info);
				printf("                     ");
			}
			pos_info.X = 0;
			pos_info.Y = 2 * MineWindowSize + 3;
			SetConsoleCursorPosition(info, pos_info);
			printf("Time (mm:ss): %d:%d", minuti, time_seconds);
			if (SAVE_RECORDS)
			{
				pos_info.X += 19;
				SetConsoleCursorPosition(info, pos_info);
				printf(". Current Best time(in ss): %d", BestResult);
			}
			if (solution)
			{
dead:
				if (!information)
				{
					pos_solution.Y = 0;
					pos_solution.X = 3 * MineWindowSize;
					SetConsoleCursorPosition(solut, pos_solution);
					
					//ShowSolution(HiddenMinesArray, MineWindowSize);
					for (i = 0; i < 2 * MineWindowSize + 1; i++)
					{
						for (j = 0; j < 2 * MineWindowSize + 1; j++)
						{
							printf("%c", HiddenMinesArray[i * (2 * MineWindowSize + 1) + j]);
						}
						pos_solution.Y += 1;
						pos_solution.X = 3 * MineWindowSize;
						SetConsoleCursorPosition(solut, pos_solution);
					}
					
				    // tozi cikyl oprintira Matricata za rekursiq izpolzvana ot funkciq OpenNearbySquares
					if (SHOW_NEAREST_EMPTY_SQUARES_MATRIX)
					{
						pos_solution.X = 4 * MineWindowSize;
						SetConsoleCursorPosition(solut, pos_solution);
						for (i = 0; i < MineWindowSize; i++)
						{
							for (j = 0; j < MineWindowSize; j++)
							{
								printf("%d", prcessedRecurseArray[i * MineWindowSize + j]);
							}
							//printf("\n");
							pos_solution.Y += 1;
							pos_solution.X = 4 * MineWindowSize;

							SetConsoleCursorPosition(solut, pos_solution);
						}
					}
				}
			}
			if (ClearSolution)
			{
				pos_solution.X = 3 * MineWindowSize;
				pos_solution.Y = 0;
				SetConsoleCursorPosition(solut, pos_solution);
				ClearSolution = 0;
				solution = 0;
				for (i = 0; i < 2 * MineWindowSize + 1; i++)
				{
					for (j = 0; j < 2 * MineWindowSize + 1; j++)
					{
						printf(" ");
					}
					pos_solution.Y += 1;
					pos_solution.X = 3 * MineWindowSize;

					SetConsoleCursorPosition(solut, pos_solution);
				}
			}
			if (information && iterationNumber!=0)
			{
				if (!solution)
				{
					pos_info.Y = 0;
					pos_info.X = 3 * MineWindowSize;

					SetConsoleCursorPosition(info, pos_info);
					for (i = 0; i < 10; i++)
					{
						printf("%s",infos[i]);

						pos_info.Y += 1;
						pos_info.X = 3 * MineWindowSize;

						SetConsoleCursorPosition(info, pos_info);
					}
				}
			}
			if (ClearInformation)
			{
				pos_info.X = 3 * MineWindowSize;
				pos_info.Y = 0;
				SetConsoleCursorPosition(info, pos_info);
				ClearInformation = 0;
				information = 0;
				for (i = 0; i < 10; i++)
				{
					for (j = 0; j < 75; j++)
					{
						printf(" ");
					}
					pos_info.Y += 1;
					pos_info.X = 3 * MineWindowSize;

					SetConsoleCursorPosition(info, pos_info);
				}
			}

			if (Death || Win) break;
			pos.X = 0;
			pos.Y = 0;
			SetConsoleCursorPosition(output, pos);

			fflush(stdin);
			Sleep(200);
		}

		pos.X = 0;
		pos.Y = 2 * MineWindowSize + 5;
		SetConsoleCursorPosition(output, pos);
		if (Death && !pass) 
		{
			pass = 1;
			goto dead;
			printf("Game over\n");
		}
		if (Win)
		{
			NumberOfDigits = 0;
			BestResult2 = BestResult;
			if ((BestResult > (minuti * 60 + time_seconds)) && SAVE_RECORDS)
			{
				BestResult = minuti * 60 + time_seconds;
				printf("Bravo\nWanna save your time? \n1:yes\n2:No\n");
				scanf("%d", &userChoice);
				if (userChoice == 1)
				{
					namereno = 0;
					BestResult2 = BestResult;
					do{
						NumberOfDigits++;
						BestResult2 = BestResult2 / 10;
					} while (BestResult2);

					if (NumberOfDigits == 3) sprintf(MineSearchStringInFile, "%dx%d-%dmines %d", MineWindowSize, MineWindowSize, NumberOfMines, BestResult);
					if (NumberOfDigits == 2) sprintf(MineSearchStringInFile, "%dx%d-%dmines  %d", MineWindowSize, MineWindowSize, NumberOfMines, BestResult);
					if (NumberOfDigits == 1) sprintf(MineSearchStringInFile, "%dx%d-%dmines   %d", MineWindowSize, MineWindowSize, NumberOfMines, BestResult);

					sprintf(anotherUselessString, "%dx%d-%dmines", MineWindowSize, MineWindowSize, NumberOfMines);
					fp = fopen("RecordList.txt", "rt");
					if (fp != NULL)
					{
						for (i = 0; i < 25; i++) // read every line from file (first 25)
						{
							size = ftell(fp);
							fscanf(fp, "%s %d", RecordListItems_strings, &BestResult2);  //%[^;] instead of %s 
							if (!(strcmp(RecordListItems_strings, anotherUselessString)))
							{
								namereno = 1;
								fclose(fp);
								break;
							}
						}
					}

					fp = fopen("RecordList.txt", "r+t");
					if (!namereno)
					{
						fseek(fp, 0, SEEK_END);
						size = ftell(fp);
						fseek(fp, size, SEEK_SET);

					}
					else
					{
						fseek(fp, size, SEEK_SET);
						fputc('\n', fp);
					}
					fputs(MineSearchStringInFile, fp);
					fputc('\n', fp);
					fclose(fp);
				}
			}
			else
			{
				printf("Bravo\n");
				fprintf(fp, "%d", BestResult);
			}
			fclose(fp);

		}
		fflush(stdin);
		printf("\nanother game?\nY/n\nyour choice: ");
		scanf("%c", &NewGameChoice);
		
		free(HiddenMinesArray);
		free(MinesArray);
		if (NewGameChoice == 'n' || NewGameChoice == 'N') break;
	} // new game cycle
	
	return 0;
}
