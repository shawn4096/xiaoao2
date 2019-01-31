// zayilama.c 杂役喇嘛
// by iceland

#include <ansi.h>
inherit NPC;
#include "name.h";

void create()
{
    string name,m1,m2,m3,m4;
    int i;
    i=random(4);
m1=names[i][random(sizeof(names[i]))];	
m2=names[0][random(sizeof(names[0]))];
m3=names[1][random(sizeof(names[1]))];
m4=names[2][random(sizeof(names[2]))];

switch (random(3)){
	case 0:  
        name = m1+m2; 
 	break;
	case 1: 
        name = m1+m2+m3; 
	break;
	case 2:
        name = m1+m2+m3+m4 ;  
	break;
	} 

      set_name(name, ({"zayi lama","lama","zayi"}));
	set("long",@LONG
他是大轮寺的杂役喇嘛，只会些粗浅功夫，在寺里身份最低，日常干些粗活重活。
LONG
	);

	set("gender", "男性");
	set("attitude", "heroism");
	set("title" , HIW"大轮寺杂役喇嘛"NOR);
	set("age", random(20)+20);
	set("shen_type", 0);
	set("str", random(10)+10);
	set("int", 20);
	set("con", random(10)+10);
	set("dex", random(10)+10);
	set("max_qi", 4500);
	set("eff_jing", 3000);
	set("max_jing", 3000);
	set("neili", 3500);
	set("max_neili", 100);
	set("combat_exp", 4300000);
	set("unique", 15);

	set_skill("force", 350);
	set_skill("dodge", 350);
	set_skill("strike", 350);
	set_skill("mizong-fofa", 150);
	set_skill("parry", 350);
	set_skill("huoyan-dao", 350);
	set_skill("yuxue-dunxing", 350);
	set_skill("longxiang-boruo", 350);
	map_skill("force", "longxiang-boruo");
	map_skill("parry", "huoyan-dao");
	map_skill("strike", "huoyan-dao");
	map_skill("dodge", "yuxue-dunxing");
	prepare_skill("strike","huoyan-dao");

	setup();
        carry_object(__DIR__"obj/qinxiu-jiasha")->wear();
}
