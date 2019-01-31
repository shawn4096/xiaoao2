#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
         set("short",HIR"������"NOR);
       set("long", @LONG
һ���������ң���������ľ���ɣ�������ɽ�������ı����𣬶���ʯ
�ڡ����ɽ��ʯ�ң����ǻ�Ȼ��ɣ�������ǰ����ɮ���������ǻۣ������
����ɽ�����ˡ��������ͨ�������겻Ϣ�����й������ҷ�ķ�������
��ͬ������ǧ�����������ơ�ְ��ɮ�ڵ����Ĵ�Ѳ�ӣ��Ա����衣һλ��
ɮ�Ŀ���������Ӳ�����
LONG
     );
	set("exits", ([
                "south" : __DIR__"xcping",
                "west" : __DIR__"xclang",
              "north"  : __DIR__"duanya",
	]));

        set("objects",([
           "/kungfu/class/shaolin/fangsheng" : 1,
        ]));

        set("coor/x",60);
  set("coor/y",420);
   set("coor/z",130);
   setup();
}
void init()
{
	add_action("do_canchan","canchan");
}


int do_canchan(string arg)
{
	int i,j,total;
	object me=this_player();

	if (!arg||arg!="��Ӱ�����Ⱦ���")
		return notify_fail("��Ҫ����ʲô��\n");
	if (!me->query_temp("rysxt/askfangsheng"))
	{
		return notify_fail("�˵����������°����õ���Ҫ�أ���Ͳ��������¾���׷ɱ��ô��\n");

	}
	if (me->query("quest/sl/rysxt/pass"))
	{
		return notify_fail("���Ѿ�����Ӱ���������а��ض����ܳɹ��ˣ�\n");

	}

	if( time()- me->query("quest/sl/rysxt/time")<86400)
		return notify_fail("�������ڽ������Ƕ�����������̫Ƶ����");

	message_vision(HIY"$N���շ�����ʦ��ָ�㣬��ϥ��������ʼ�������״̬��\n"NOR,me);
	total=random(me->query("str"));

	i = 20;
	if(me->query("m-card-vip")) i =  18;
	if(me->query("y-card-vip")) i =  15;
	if(me->query("buyvip"))     i =  10;
	i=random(i);

	j=random(me->query("kar"));

	if( i<3 
		&& me->query("kar")<31
		&& total>40
		&& j > 26 ) 
	{
		tell_object(me,HIY"\n�������������ȷ����ݺύ������Ӱ�����ȵ���������ĵá�\n"NOR);
		tell_object(me,HIG"\n���֮�䣬������ͨ�������Ͼ�����ͨ����������Ӱ�����ȷ���Ҫּ��\n"NOR);
		tell_object(me,HIR"��ϲ������Ӱ�����Ⱦ����ɹ�!\n"NOR);
		me->set("quest/sl/rysxt/pass",1);
		log_file("quest/rysxt", sprintf("%8s(%8s) ʧ��%d�κ�ѧ����Ӱ�����Ⱦ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|����������totalȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/sl/rysxt/fail"),i,j,total,me->query("kar"),me->query("combat_exp")) );
		me->delete_temp("rysxt");
		return 1;
		
	}	
   else
	{
		log_file("quest/rysxt", sprintf("%8s(%8s) ������Ӱ�����Ⱦ���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|����������totalȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/sl/rysxt/fail"),i,j,total,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"����ϸ����������ʦ��ָ�㣬���Ƕ���Ӱ�����ȵİ���ȫȻ����Ҫ�졣\n\n"NOR);
		me->add("quest/sl/rysxt/fail",1);
		me->set("quest/sl/rysxt/time",time());
		me->start_busy(1+random(3));
		me->delete_temp("rysxt");
		tell_object(me,"�ǳ��ź�,������Ӱ������ʧ��"+me->query("quest/sl/rysxt/fail")+"�Ρ�\n");
		return 1;
	}

}


