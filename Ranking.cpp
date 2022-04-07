#include"Ranking.h"
#define NUM_MVP 5
static PlayInfo MVP[NUM_MVP];
static int nMVP = NUM_MVP;


static void initRanking()
{
	PlayInfo noname = { "c++ 좋아요",1000,1000.0 };
	for (int i = 0; i < nMVP; i++)
		MVP[i] = noname;

}

void loadRanking(const char* fname)
{
	FILE* fp = fopen(fname, "r");
	if (fp == NULL)
		initRanking();
	else
	{
	for (int i = 0; i < nMVP; i++)
	fscanf_s(fp, "%d%s%f", &MVP[i].nMove,MVP[i].name, &MVP[i].tElapsed);
		fclose(fp);
	}
}

void storeRanking(const char* fname)
{
	FILE* fp = fopen(fname, "w");
	if (fp == NULL) return;
	for (int i = 0; i < nMVP; i++)
		printf_s("[%2d위] %4d %-16s %5f\n", i + 1, MVP[i].nMove,
			fprintf(fp, "%4d%-16s%-5.1f\n", MVP[i].nMove, MVP[i].name, MVP[i].tElapsed));
	fclose(fp);
}

void printRanking()
{
	for (int i = 0; i < nMVP; i++)
		printf_s("[%2d위] %4d %-16s %5.1f\n",i+1,MVP[i].nMove,
			MVP[i].name, MVP[i].tElapsed);
}

int addRanking(int nMove, double tElap)
{
	if (nMove < MVP[nMVP - 1].nMove)
	{
		int pos = nMVP - 1;
		for (; pos > 0; pos--)
		{
			if (nMove >= MVP[pos - 1].nMove)break;
			MVP[pos] = MVP[pos - 1];

		}
		MVP[pos].nMove = nMove;
		MVP[pos].tElapsed = tElap;
		printf("%d위 입니다. 이름을 입력하세요:", pos + 1);
		scanf_s("%s", MVP[pos].name);
		return pos + 1;

	}
	return 0;
}
