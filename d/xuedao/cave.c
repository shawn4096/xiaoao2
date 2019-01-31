// nroad6.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",RED"����"NOR);
        set("long",@LONG
����һ��Ѫ����ɽ����������Ϊ���ء��������и����ڴ�ѩɽ��
���������ھ���ɣ��������ǿ������ܸ��ܵ�΢΢������������Ȼ��
�����ⲿ��ͨ���¶������ܰڷ����������ӣ���������һ��Ѫ��ɫ��
�����Σ���������Ѫ��ɫ��һ��ë̺�����ǿֲ���
LONG );
        set("exits",([
                "north"   : __DIR__"shitang",
                "west" : __DIR__"xiuxishi",
			    "east" : __DIR__"lingwushi",
			    "south" : __DIR__"shandong3",


        ]));
        set("objects",([
             /*  "/clone/weapon/miandao" : 1,
				
				"/clone/weapon/xinyuedao" : 1,*/
			//	"/clone/weapon/blade" : 1,

        ]));
        //	set("no_clean_up", 0);
       // set("outdoors", "xuedao");
        setup();
       //        replace_program(ROOM);
}

//���վ�3��ʼ��־Ϊ ���������Ҫ���� szj/wait_baohu

void init()
{
        object me=this_player();
		object oba;
	//add_action("do_watch", "mianbi");
        add_action("do_baohu", "baohu");
	    add_action("do_qiang", "qiang");
		if (me->query_temp("szj/wait_baohu"))
		{
			oba=new(__DIR__"npc/shuisheng.c");
		    oba->move(environment(me));
		    message_vision(HIC"\nˮ�ϻŻ����ŵ����˽�������ɫ�԰ף�����������\nһ���ܣ�һ�߲�ס��󿴣��ƺ�������������׷���Ƶá�\n"NOR, me);
			call_out("shuisheng",3,me);
		}
}
void shuisheng(object me)
{
        object obb,room;
		if (!present("xuedao laozu",environment(me)))
        {
			room=load_object("/d/xueshan/xuegu");
			if (obb=present("xuedao laozu",room))
			{
				message_vision(HIY"\nѪ�������Ȼ�Ӷ���Ծ������ɫ���Եض�ˮ��Ц��������ү���׽�˸���ƷС椡�\n"NOR,me);
				obb->move(environment(me));
			}
			else
			{
              obb=new("/d/xueshan/npc/laozu.c");
		      obb->move(environment(me));
		      message_vision(HIY"\n���⴫��һ����Ц��һ��ɫ���е��Ϻ��п����������У������������\n"NOR,me);
			}
        }
}

int do_baohu(string arg)
{
	object me = this_player(),ob,weapon;
	
	if (!me->query_temp("szj/wait_baohu")) return 0;
	if (arg != "shui sheng") return 0;
	me->delete_temp("szj/wait_baohu");
	ob = present("xuedao laozu", this_object());
	weapon=ob->query_temp("weapon");
	message_vision(HIW"$N�е���������ɱ���ˣ���˵���˽���ȥ��������֦����$n���ϡ�\n"NOR, me, ob);
	message_vision(HIC"����ƽʱ��$n���ܸ�$N���У�����ʱ˥��֮�࣬��������ԭ���İ�ɣ���ָһ�ɣ�"+weapon->query("name")+HIC"������ء�\n"NOR, me, ob);
	weapon->move(environment(me));
	me->set_temp("szj/baohu", 1);
	me->set_temp("szj/wait_qiang", 1);
	return 1;
}
int do_qiang(string arg)
{
	object me = this_player(), ob;
	if (!me->query_temp("szj/wait_qiang")) return 0;
	if (arg != "dao" && arg !="blade") return 0;
	me->delete_temp("szj/wait_qiang");
	ob = present("xuedao laozu", this_object());
	message_vision(HIW"$N��$nͬʱ����ȥ�����С�$N�������£��Ȱ����˵�����\n"NOR, me, ob);
	message_vision(HIC"$n����˫�֣�����$N���ж�ȥ��$Nһ����Ϣ���ſ���Ѫ�������ֳų֡�\n"NOR, me, ob);
	message_vision(HIC"$n֪���Լ������޶࣬��һ��������$N�������Լ�����ɥ$N�֡�\n"NOR, me, ob);
	message_vision(HIC"$Nͷ����Ѫ��ɮ��ס������Խ��Խ���ѣ��ؿ��������ѡ�\n\n"NOR, me, ob);
	me->start_busy(100);
	call_out("story3", 2, me, ob);
	return 1;
}


void story3(object me, object ob)
{
	if (me->query_skill("shenzhao-jing", 1) < 200) {
		call_out("finish", 1, me, ob);
		return;
	}
	tell_object(me, HIR"����л����ŵ�һ�����������ϳ壬Ҫ�ӿڱ��к��˳���������ͷ��Ҫ�����裬������嵽��ͷ���ֻ�����ȥ��\n"NOR);
	tell_object(me, HIR"һ�������������������ͻ��ʼ���Ҳ�����·��\n"NOR);
	tell_object(me, HIR"��ֻ��ȫ�����������ѴＫ�㣬����ֻ�У����ҿ�Ҫ���ˣ��ҿ�Ҫ���ˣ���\n\n"NOR);
	call_out("story4", 2, me, ob);
}

void story4(object me, object ob)
{
	object obj;
	int lev = me->query_skill("shenzhao-jing", 1);
	if (random(150 + lev/2) > 350 && random(10)> 8 && random(me->query("kar"))> 27)
	{
	tell_object(me, HIW"ͻȻ֮�䣬��ֻ���ظ�����Ҵ�ʹ�����������Խ��Խ��Խ��Խ�ȣ�������������
û�г��ڣ�ֱҪ�Ѹ������������ǰ������֮��ġ�����Ѩ�����ƺ�������������һ��С
�ף���ʱ������˿˿�����ӡ�����Ѩ��ͨ����׵ĩ�˵ġ���ǿѨ��ȥ����������������
ǿ����Ѩ��಻�����磬������������������������ǿ��ȴ�Ƕ�������������Ϣ������ͨ��
�����ڵ���Ϣ�����޷���й��һ�ɾ޴�����������ײ��������Σ��������ǿ���͹�������
��ͨ�������Ͷ����Ĵ��ѹء�����Ϣһͨ�롰��ǿѨ������ʱ�����ᡢ���ء����š�����
��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������
��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
	
	 tell_object(me, HIY"�����Ϣ�嵽�ٻ�Ѩ�У�ֻ��������һ��������һ�������Ӷ�ͷ���������ڴ�������ͨ��
�˴��µġ��н�Ѩ������н�Ѩ������������һ���Զ����Ρ�������Ѩ�����������棬��
����������Ϣһ·���У�����Ȫ����ͻ������ᡢ���ǡ��Ϲ������á����С���ͥ���β��
���ڡ����ϡ��С������䣬����ˮ�֡����ʡ�������ʯ�š���Ԫ���м���������Ѩ���ֻ�
���ˡ�����Ѩ�������һ�������н�����������֮��ȫ����˵�����ĳ������á���Ϣ��һ
��ͨ��ʱ���Ǽ��ѣ��ζ�������ͨ����·���ˣ��ڶ��Ρ�������ʱ��Ȼ��Ȼ�ķɿ���ת��
���֮�䣬������һʮ�˴Ρ�\n\n"NOR);
	message("channel:rumor", MAG"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ���ʹ���վ���ͨ���ζ��������ﵽ�����վ��ķ�����߾��磡\n"NOR, users());
	message_vision(HIC"$N���ڵľ���������ǿ������ȴ����ʮ�ֺ��£�ֻ����������˫����ץ���裬ʼ����
����$n���ϣ��������ҳż��£�ͻȻһ������$n��С������֮�ϡ�\n\n"NOR, me, ob);
	ob->unconcious();
	me->start_busy(1);
	me->set("quest/szj/pass",3);
	
	obj = present("shui sheng", this_object());
	if (!obj) return;
	message_vision(HIY"$N˵�����������߰ɣ�����$n����һ������Ź���ġ�\n"NOR, me, ob);
	message_vision(HIY"$n���һ������Ҳ���Ǻ��ˣ����Ժ󲻻�Ź���ģ�\n"NOR, me, obj);
	message_vision(HIY"$n˵�������������ȥ��\n\n"NOR, me, obj);
	destruct(obj);
  }
    call_out("finish", 1, me, ob);
		return;
	
}

void finish(object me, object ob)
{
	object obj = present("shui sheng", this_object());
	if (!obj) return;
	message_vision(HIY"$n���һ����С�����Բ��������������������Ů�˵ķ������㲻����\n"NOR, me, ob);
	message_vision(HIY"�������С��ۿɲ��ܷŹ���������������ָ��ˣ��϶���ɱ������������\n"NOR, me, ob);
	message_vision(HIY"$n�ӵ�����ˮ�ϣ�ˮ�϶�ܲ�������Ѫ�Ӻ�����ֱ��������\n"NOR, me, ob);
	obj->die();
	me->start_busy(1);
	me->unconcious();
}
