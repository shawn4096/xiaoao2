// fenghuangjiang.c ��ʽ�
// cre by sohu@xojh 2014/9
#include <ansi.h>;
inherit ITEM;
inherit F_FOOD;
void create()
{
     set_name(HBYEL+HIW"��ʽ�"NOR, ({"fenghuang jiang","fenghuang","jiang"}));
     set_weight(25);
     if (clonep())
            set_default_object(__FILE__);
     else {
            set("unit", "ƿ");
            set("long", "����һƿ���۷����Ƶķ�ʽ����������㣬������Ƣ��\n");
            set("no_get", 1);
            set("no_drop", 1);
            set("no_give", 1); 
            set("food_remaining", 20);
            set("food_supply", 50); 
     }
     setup();
}
