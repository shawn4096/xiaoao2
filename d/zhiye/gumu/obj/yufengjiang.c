// fenghuangjiang.c ��ʽ�
// cre by sohu@xojh 2014/9
#include <ansi.h>;
inherit ITEM;
inherit F_FOOD;
void create()
{
     set_name(HBYEL+HIW"��佬"NOR, ({"yufeng jiang","yufengjiang","jiang"}));
     set_weight(25);
     if (clonep())
            set_default_object(__FILE__);
     else {
            set("unit", "ƿ");
            set("long", "����һƿ���۷����Ƶķ�ʽ����������㣬������Ƣ��\n");
            //set("no_get", 1);
            //set("no_drop", 1);
            //set("no_give", 1); 
			set("value",500);
            set("food_remaining", 50);
            set("food_supply", 50); 
     }
     setup();
}
