#include <ansi.h>
#include <weapon.h>
inherit COMBINED_ITEM;
inherit THROWING;

#include "/inherit/item/embed.h"

void create()
{
       set_name(HIC "�����滨��" NOR, ({"zhen", "lihuan zhen","noodle"}));
	   set_weight(100);

       if( clonep() )
               set_default_object(__FILE__);
  
     else {
               set("long", "�����ƽ��ϻ�����ߴ磬�����硣����С׭�����̣������ؼ�Ѫ���ջز��飻����֮��������֮������\n����֮ʱ����������ʮ��ö���뼤��������˵��������ޱȡ�\n");
			   set("unit", "��");
               set("no_sell", 1);
			   //set("unique", 1);

			   set("value", 72000);
               set("base_unit", "ö");
               set("embed", 1);

               set("damage", 50);
  
			   set("base_weight", 10);
       }
       set_amount(365);
       init_throwing(60);
	   setup();

}

