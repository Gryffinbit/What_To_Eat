---
title: 帮你决定吃什么
author: Gryffinbit
mathjax: true
date: 2021-05-12 08:21:53
tags: C
categories: 创意开发
---

每到饭点，又到了世纪难题“一会吃什么？”。于是用C写了这个简单的小代码来解决这个世纪难题。

## 设计思路

1. `typedef` 一个结构体`Food`，数据元素为菜的ID，菜名，这道菜所处区域。

2. `void iterm()`需要有一个菜单导入的功能，把可供选择的菜放进去。

   用到了`fopen`   `fscanf` `fclose`函数来读取文件。导入的菜单，格式要求，用空格来隔开三个元素。读取成功后，将内容分门别类的存入到结构体每个元素的数组中

3. `void classify` 选择去哪吃，以便后续根据选择的地点，来筛选出符合所在地附近的菜。

4. `void avaliable()`决定了去哪里吃之后，筛选出菜单中符合条件的地方

   用到了`strcmp`来对比两个数组中的内容是否一致。输入的位置和菜单中某些菜的位置一致，则将符合条件菜的ID存入`avali_i[ ]`符合条件数组。av_num是符合条件菜的数量。

5. `void generate(void)` 随机数生成，让生成的随机数来决定吃什么

6. `void convert()` 将生成的随机数，与菜名的ID相对应上，显示结果的时候，就只显示菜名

## 结果展示

![](https://gryffinbit-1304014832.cos.ap-chengdu.myqcloud.com/Blog/eat(1).png)



## 完整代码

```C
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
```

## 菜单

```markdown
0 芙蓉食堂1楼 芙蓉食堂附近
1 芙蓉食堂2楼 芙蓉食堂附近
2 前街过桥米线 芙蓉食堂附近
3 前街鱼粉 芙蓉食堂附近
4 前街铁板烧 芙蓉食堂附近
5 前街老麻抄手 芙蓉食堂附近
6 农贸鸭血粉丝 网安院附近
7 农贸无骨鱼 网安院附近
8 农贸冒菜 网安院附近
9 农贸曹氏鸭脖 网安院附近
10 农贸外诊旁的面 网安院附近
11 农贸小丫家 网安院附近
12 农贸正新鸡排 网安院附近
13 农贸钵钵鸡 网安院附近
16 清吧螺蛳粉 网安院附近
17 清吧咖喱饭 网安院附近
18 清吧石锅拌饭 网安院附近
19 东苑夺笋面 东苑
20 东苑黄焖鸡 东苑
21 东苑巴老冒冒菜 东苑
22 东苑螺蛳粉 东苑
23 东苑石锅拌饭 东苑
24 东苑麻辣烫 东苑
25 东苑鸡公煲 东苑
26 东苑荤豆花 东苑
27 东苑火锅冒菜 东苑
28 香樟食堂清汤面 香樟
29 香樟食堂豆汤饭 香樟
30 香樟食堂干锅 香樟
31 香樟食堂铁板烧 香樟
32 香樟食堂鸭血粉丝 香樟
33 香樟食堂土豆粉 香樟
34 香樟食堂意大利面 香樟
35 香樟韩国料理 香樟
36 香樟二楼的面 香樟
37 香樟食堂烤鱼 香樟
38 香樟食堂汉堡 香樟
39 香樟食堂肥肠粉 香樟
40 后街馄饨大王 后街附近
41 后街烤冷面 后街附近
42 后街关东煮 后街附近
43 后街热干面 后街附近
44 后街炸鸡 后街附近
45 后街手抓饼 后街附近
46 后街炸酥肉炸平菇 后街附近
47 理工宾馆酸辣粉 后街附近
48 理工宾馆饺子 后街附近
49 理工宾馆冒菜 后街附近
50 理工宾馆砂锅 后街附近
51 理工宾馆烤肉饭 后街附近
52 巷子里清吧煎蛋面 网安院附近
53 农贸凉面凉皮 网安院附近
```





## 控诉权哥

写完代码，功能实现有点小bug，于是就扔给权哥调试了。当时写的时候，很碎片化，思路也乱七八糟，想到哪里加哪里，于是变量名，全局变量都定义的乱七八糟的。看着他调试的时候，我对着代码随口来了句，什么狗屎代码。

于是他说：“是啊，谁写的啊，哦，我明白了。狗拉的代码，就叫狗屎代码。”

。。。。。。。阿呸，每日思考，这样的人，为什么会有女朋友啊。

