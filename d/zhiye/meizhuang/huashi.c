// Room: /d/meizhuang/huashi.c
// By Lklv
// add by sohu#xojh ��ī
#include <ansi.h>
inherit ROOM;
int do_guanmo(string arg);
void create()
{
	set("short", "����");
	set("long", @LONG
����һ�仭�ң�������������ڷ��ż������ӣ��ı��Ϲ��ż��������Զ
�ľ��ᡣ�߽�����ϸ����ֻ��һ����ˮī���࣬�ʷ����񹤡����߷��裬��
Ȼ���Դ��֮�֣�����������һ��ˮī���˱���ͼ��(hua)��ī�����죬����
�۽�,�����̲�ס��ʼ��Ħ(guanmo)������

LONG
	);
	set("exits", ([
		"east" : __DIR__"huilang6",
	]));

        set("objects", ([
                __DIR__"npc/danqingsheng" : 1,
        ]));
    set("item_desc", ([
          "��" :  HIC"����������һ�����˵ı��棬ī�����죬�����۽������䲻������ \n"+
							"ȴҲ֪ȷ���������ּ���������ǣ����������������ī�����֡�\n"+
							"�˵��Ǳʷ�ɭ�ϣ�һ�ʱʱ��糤���Ĵ̻��������ǻ������"HIG"����"HIC"�֡�\n"+
		 					"�����л��У����ƺ��̲���һ�׼������Ľ�����\n"NOR,
		  "hua" :  HIC"����������һ�����˵ı��棬ī�����죬�����۽������䲻������ \n"+
							"ȴҲ֪ȷ���������ּ���������ǣ����������������ī�����֡�\n"+
							"�˵��Ǳʷ�ɭ�ϣ�һ�ʱʱ��糤���Ĵ̻��������ǻ������"HIG"����"HIC"�֡�\n"+
							"�����л��У����ƺ��̲���һ�׼������Ľ�����\n"NOR,
       ]));
	setup();
}
void init()
{
	
        add_action("do_guanmo", "guanmo"); 
       
}

int do_guanmo(string arg)
{
    int j;
	
	object me=this_player();
    if (me->query("family/family_name")!="�������")
       return notify_fail("�㲻������̵��ӣ������������������\n");
	if (!arg||arg!="��")
	   return notify_fail("��ɵվ�Ķ���ʲô��\n");
	if (!me->query_temp("qxwxj/pomoask"))
	   return notify_fail("���ǵ������Ļ��ң�İ���˲�Ҫ�ҹ�Ħ��\n");
	if (me->query("quest/hmy/qxwxj/pomo/pass"))
	   return notify_fail("���Ѿ������˽���ī���齣�����ٿ������κζ�����\n");
    if (time()-me->query("quest/hmy/qxwxj/pomo/time")<86400)
       return notify_fail("������Ҳ̫�ڿ���ˣ�\n");
    j=random(me->query("kar"));
	
	if (arg=="��"||arg=="����")
    {
       message_vision(HIW"$N�ۿ����ˮī������ͼ��ī�����죬�ݺ����أ����Ʋ����������۽���\n"NOR,me);
	   message_vision(HIC"$N��Ŀ��۽�����������ֺ󣬺���һ�ɽ����糤ǹ��ꪣ�ӭ�������\n"NOR,me);
	   if (me->query("kar")<31
		&& j>=25
		&& me->query("int")>=25)
	    {
          
	      message_vision(HIY"�����㽫Ŀ�⡰�������������ī����˸��ֺ󣬾����⼸�����ƺ���Щ��ͬ��\n"+
						"�˵��Ǳʷ�ɭ�ϣ�һ�ʱʱ��糤���Ĵ̻��������ǻ�����������֣����ǳ�������������\n"NOR,me);
	      message_vision(HIC"$N��ϲ�㣬��������������������ī���齣�����������С�\n"NOR,me);
	  
	   log_file("quest/pomopimajian",sprintf("%s(%s) ��÷ׯ���ң�������������ī���齣�ľ�������Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,me->query("quest/hmy/qxwxj/pomo/fail"),me->query("combat_exp"),me));
	   
	   me->set("quest/hmy/qxwxj/pomo/pass",1);
	   me->delete_temp("qxwxj/pomoask");
	   me->delete_temp("givehua");
	   me->start_busy(1);
	   return 1;
	  }
	   else {
		message_vision(HIY"\n$N��Ȼ֪���������ͬѰ���������˰���ȴһʱ֮��ȴ��������⡣�����㻹���д���������������ѧϰ�ˡ�\n"NOR,me);
	    log_file("quest/pomopimajian",sprintf("%s(%s) ������ī���齣�ľ���ʧ�ܡ���Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,me->query("quest/hmy/qxwxj/pomo/fail"),me->query("combat_exp"),me));
		me->add("quest/hmy/qxwxj/pomo/fail",1);
		me->set("quest/hmy/qxwxj/pomo/time",time());
		me->delete_temp("qxwxj/pomoask");
	    me->delete_temp("givehua");
		me->start_busy(1);
        return 1;
	   }
	
    }

}


