// by tangfeng 8/2004

#include <ansi.h>
inherit ITEM;

#define QUESTDIR5 "quest/ѩɽ�ɺ�/����/"
#define QUESTDIR4 "quest/ѩɽ�ɺ�/�书/"

void create()
{
        set_name(HIW"ֽ��"NOR, ({ "zhi tuan", "zhituan", "paper"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ����ֵ�ֽ�ţ�չ��֮���ƺ���¼һЩ�ڹ������з�����\n"); 
                set("unique", 1);
                set("treasure", 1);
                set("material", "silk");
                set("no_give", "�������������뿪�㡣\n");
                set("no_get", "�������������뿪�Ƕ���\n");
        }
}
void init()
{
          if(!this_object()->query("owner")) return;
     	  add_action("do_yanjiu", "yanjiu");	
     	  add_action("do_yanjiu", "find");
}

int do_yanjiu(string arg)
{
	int i,j,total;

	object obj,me = this_player();        		       
	if (!(arg=="zhi tuan" || arg == "zhituan" || arg == "paper")) return 0;
	if ( me->is_busy()) 
		return notify_fail("��������æ���ء�\n");
	if( me->is_fighting() ) 
		return notify_fail("���޷���ս������������顣\n");
	if (!id(arg))
		return notify_fail("��Ҫ��ʲô��\n");
        if( !me->query(QUESTDIR5+"shuku")||me->query(QUESTDIR5+"shuku")<3)

			return notify_fail("�������������ֽ�Ű���\n");
	if(this_object()->query("owner")!=me->query("id"))
		return notify_fail("�������������ֽ�Ű���\n");
	if (me->query(QUESTDIR4+"lengquanshengong"))
		return notify_fail("���Ѿ�������Ȫ�񹦵�����������\n");
	if(!present("tishi ka",me))
	{
  		message_vision(HIY"ͻȻһ����Ӱ������$N��ǰ���ݸ�$Nһ�ſ�Ƭ��\n"NOR, me);
  		tell_object(me,YEL"���ͷһ������һ����ʾ������ͷ��һ������Ӱ�Ѿ�����������˧Ŷ~~~~~��\n"NOR);
  		obj=new(__DIR__"tishika");
  		obj->move(me);
		me->start_busy(2);
		tell_object(me,YEL"�㻹�����濴һ����ʾ�������ݣ���Ҫ���ڳ嶯��\n"NOR);
  		return 1;
	}
	j=random(me->query("kar"));
	i = 20;
	total=me->query("int")+me->query("dex")+me->query("str")+me->query("con");
    
	if(me->query("m-card-vip")) i =  18;
    if(me->query("y-card-vip")) i =  15;
    if(me->query("buyvip"))     i =  10;
	i= random(i);
	
	if( i==2

	  && random(total) > 150
	  && me->query("kar")<31 
	  && j>28)
  
	{
	  tell_object(me,HIG"��ͻȻ���������ߴ���Ĳ����书�ؼ���ȴ��һ���ر��ĵص㡣\n"NOR);
	  tell_object(me,HIG"����ϸ�о�ֽ�ŵ����ݣ��ص�Ӧ�þ��ڸղž������鷿�\n"NOR);
	  tell_object(me,HBGRN+HIW"\n\n��ϲ�㣡��������Ȫ���ռ����ص���Ҫ������\n"NOR);

	  me->set(QUESTDIR4+"lengquanshengong", 1);
	  me->start_busy(2);
	  log_file("quest/feihulengquan", sprintf(HIR"%s(%s) �ɹ��⿪��Ȫ�񹦡���Դ��%d�����飺%d��\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
  }
  else
  {
	  tell_object(me,HIY"\n�㰴��ֽ���ϵ���Щ��������ȫ����������ȫ���ô�������˵����书�ˡ�\n"NOR);
	  log_file("quest/feihulengquan", sprintf("%s(%s) ��ͼ�⿪��Ȫ��ʧ�ܡ����飺%d����Դ��%d��\n", me->name(1),me->query("id"), me->query("combat_exp"),me->query("kar")) );
	  tell_room(environment(me),HIY""+me->name()+"˳�ֶ���һ��ֽ�š�\n"NOR, ({}));
	  if(me->query(QUESTDIR5+"shuku")==2 && me->query("registered")>=3)
	  {
        tell_object(me,HIR"\n��ΪVIP��ݣ�����Լ���ʹ�����������ҵ�����һ��ֽ�š��������޴λ��ᡣ\n"NOR);
		tell_object(me,HIR"���������ΪĿǰ���Բ��û��������ѣ������Ժ�����������������������˷ѡ�\n"NOR);
	  }
	  me->start_busy(2);
	  destruct(this_object()); 
  }
	return 1;	    
}
