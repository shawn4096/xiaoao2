//���շ�

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", HIR "���շ�" NOR);
	set("long", 
"�������"HIG"��ɽ���շ�"NOR"��������һվ,�㲻����һ��:\n\n"
"          ���������,ǧɽĺѩ,ֻӰ��˭ȥ?\n\n"
"�ĸо�,�����м���ʯͷ,���������ʿƽʱ���������ĵط�!\n"
"ȴ����ɽ���ƣ��紵����(songtao)�������򽣷��裬���ز���һ��!\n\n"

);
	set("outdoors", "��ɽ");

	set("exits",([
		"west":__DIR__"fengchantai",
	]));
	setup();
}

void init()
{
	add_action("do_guan", "guan");
	add_action("do_lingwu", "guanwu");
}

int do_guan(string arg)
{
	object me=this_player();
	if (me->is_busy())
		return notify_fail("��������æ���أ�\n");
	if( !arg || arg=="" ) return 0;
	if( arg=="sun" ){
		message_vision("$N��ʯͷ��һվ,���Ÿո������̫��,��������ڤ˼��\n", me);
		return 1;
	}
}

int do_lingwu(string arg)
{
	object me=this_player();
	if (me->query("family/family_name")!="��ɽ��")
		return notify_fail("ֻ����ɽ�ɵ��Ӳſ����������η���\n");
	if (!me->query_temp("feiwu/askfei"))
	{
		return notify_fail("��������첻��Ҫ�죬������û�õ�ʦ��ָ�㰡��\n");
	}

	if (!arg || arg!="songtao")
		return notify_fail("��Ҫ����ʲô\n");
	if (me->query_skill("songshan-jian",1)<200)
		return notify_fail("�����ɽ�����ȼ�̫��,����200��������ʲô���ݡ�\n");

	if (me->query("quest/ss/ssjf/feiwu/pass"))
			return notify_fail("���Ѿ��⿪�����η����������û����ɧ����!\n");
      if (time()-me->query("quest/ss/ssjf/feiwu/time")<86400)
			return notify_fail("��Ҳ̫�ڿ���ˣ�������Ҫ����Ŭ���ź�!");
        //���״̬
		me->set("quest/ss/ssjf/feiwu/time",time());
		me->set("quest/ss/ssjf/feiwu/exp",me->query("combat_exp"));
		message_vision(HIC"�紵������������������ǧ������$N������ʦ�����Ե��������ν��⣬�ƺ���Щ�ĵá�\n",me);
      if(random(me->query("kar"))> 25) 
	     {
			
		    message_vision(HIY"\n\n�������ϲ���$N�������������η��������Ҫּ��\n",me);
		    me->set("quest/ss/ssjf/feiwu/pass",1);
			log_file("quest/ssjffeiwu", sprintf("%s(%s) ʧ��%d�γɹ��⿪��ɽ�������������Դ��%d�����飺%d��\n",   
             me->name(1),
             me->query("id"), 
             me->query("quest/ss/ssjf/feiwu/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			 me->start_busy(1);
			 return 1; 
			
		  }
		  else {
	   	    message_vision(HIG"����ʧ�ܣ��㲻����Щ����ɥ��������������أ�����첻�����ƺ��������������ǰ��\n",me);
			me->set("quest/ss/ssjf/feiwu/time",time());
			me->set("quest/ss/ssjf/feiwu/exp",me->query("combat_exp"));	
			log_file("quest/ssjffeiwu", sprintf("%s(%s) ����ɽ������ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
             me->name(1),
             me->query("id"), 
             me->query("quest/ss/ssjf/feiwu/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			me->add("quest/ss/ssjf/feiwu/fail",1);
			return 1;
		  }
		

	

}