#include <ansi.h>;
inherit ITEM;

void create()
{
     set_name(HIY"��Կ��"NOR, ({"jin yaoshi","gold key","key"}));
     set_weight(10);
     if (clonep())
           set_default_object(__FILE__);
     else {
           set("unit", "��");
           set("long", "����һ�Ѵ�����Ƶ�Կ�ף�����������������ƺ��ʹ����µ�ĳЩ�����йء�\n");
           set("unique", 1);
           set("value", 40000);
     }
     setup();
}
