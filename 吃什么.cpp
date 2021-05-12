#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Foods {
  int id;
  char name[100];
  char area[30];  //“吃什么”时的所在地
} Food;

Food food[100];
int g_i = 0;   //从文件中读入的数据，存入数组
int num;    //
char location[30];  //去哪吃
int avali_i[50] = {-1};   //符合去哪吃条件的，将菜名ID存入数组
int av_num = 0;   //符合条件的菜的数量

void iterm() { //读入菜单，并存入数组以备后面使用

  FILE* menu = fopen("/Users/gryffinbit/vscode_project/生成食物/menu.txt", "r");
  if (menu == NULL) {
    printf("File open error!\n");
    return;
  }
  while (fscanf(menu, "%d %s %s", &food[g_i].id, food[g_i].name, food[g_i].area) != EOF) {
    g_i++;
  }
  fclose(menu);
}

void classify() {   //选择去哪里吃
  printf("去哪吃呢？%s", location);
  printf("可以选择的地方：芙蓉食堂附近，后街附近，网安院附近，香樟，东苑\n");
  scanf("%s", location);
}


void avaliable() {//决定了去哪里吃之后，筛选出菜单中符合条件的地方
  for (int j = 0; j < g_i; j++) {
    if (strcmp(location, food[j].area) == 0) {
      avali_i[av_num] = food[j].id;
      av_num++;
    }
  }
}

void generate(void) {  //随机数生成
  time_t t;
  srand((unsigned)time(&t));
  num = rand() % av_num;
}

void convert() {   //将生成的随机数，与菜名的ID相对应上
  g_i = 0;
  while (avali_i[num] != food[g_i].id) {      
    g_i++;
  }
  // printf("%d %s %s\n", food[g_i].id, food[g_i].name, food[g_i].area);
  printf("❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️\n");
  printf("那就去吃 ❣️  %s ❣️  吧！\n", food[g_i].name);
}

int main() {
  iterm();
  classify();
  avaliable();
  generate();
  convert();
  return 0;
}