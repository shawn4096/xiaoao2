inherit ITEM;
#include <ansi.h>
void create()
{
       set_name(HIW"����ɢ"NOR, ({ "guangling san", "san", "guangling" }) );
       set_weight(100);
       if( clonep() )
               set_default_object(__FILE__);
      else {
               set("unit", "��");
                set("long", "����һ������ɢ�����ף���÷ׯ���ҹ�����õ��Ķ�����\n");
               set("value", 100000);
               set("no_give",1);
               set("treasure",1);
               set("no_put",1);
               set("no_drop",1);
               set("material", "jade");
       }
       setup();
}
