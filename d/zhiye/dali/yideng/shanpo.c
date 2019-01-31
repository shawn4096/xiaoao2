// By River 2002.6.3

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "ɽ��");
	set("long", @LONG
ֻ��ɽ����һͷ��ţ���ׅ�������������ȴ�����졣��ţ��������һ����
ʯ�ϣ�����������վ����������ʯҡҡ���飬����һ�˰����˶��ֲ���˫����
ס��ʯ��ֻҪһ���֣��Ʊ���ţ��ʯһ�����������ȡ�������վ������һ��
ͻ�������ң��޴����ã���Ȼ�����ţ��Ҫ��������ʯѹ�����������Ƕ��֣�
Ҳ�����㡣�������ƣ�������ţ�������ϳԲݣ�ʧ�����������ײ����ʯ����
�˱��ڽ�����������ʯ��ţ��ȴ���Լ��������Ǳ����ء�
LONG
	);
	set("outdoors", "��Դ��");

	set("exits", ([
		"westdown" : __DIR__"shanding",
		"east" : __DIR__"shiliang",
	]));

	set("objects", ([
		__DIR__"npc/gengzi" : 1,
	]));

	setup();
}

void init()
{
	add_action("do_tuo", "tuo");
}

int do_tuo(string arg)
{
	object ob, me = this_player();

	if (! arg || arg != "shi")
		return notify_fail("��Ҫ��ʲô��\n");

	if ( me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");

	if ( me->query_temp("yideng/nongfu_pass"))
		return notify_fail("���Ѿ���ũ������ʯ���ˣ��������뿪��\n");

	if ( query("ppl"))
		return notify_fail("�Ѿ����������ˡ�\n");

	if ( ! ob = present("nong fu", environment(me)))
		return notify_fail("ũ���ڣ���ô���ʯ����һ�����޷����֡�\n");

	if ( me->query("neili") < 2500 )
		return notify_fail("�����������������Ҫ�������ʯ��Ƚ�Σ�ա�\n");

	message_vision(CYN"\n$N����ũ����ߣ�������ȥ������ס��ʯ�����������ţ�����ȥ��ţǣ����\n\n"NOR, me);
	me->start_busy(100);
	me->add("neili", -2500);
	set("ppl", 1);
	remove_call_out("wait");
	call_out("wait", 2, me, ob);
	return 1;
}

void wait(object me, object ob)
{
	if ( !me ) return;

	if ( !ob ) {
		remove_call_out("finish");
		call_out("finish", 0, me, ob);
		return;
	}

	message_vision(YEL"\n��$n���϶��ᣬ��������$N��ټ�������е����ţ���ʯ�������������֣�\n"+
			"������ӣ�������Ȼ����ʯ�ס�$N����̤�ȣ������ھ���˫�����Ϸ���ͦ�٣�\n"+
			"��ʯ��ʱ���������$n����Ҳ�����ˡ�\n\n"NOR, me, ob);

	remove_call_out("wait2");
	call_out("wait2", 5, me, ob);
}

void wait2(object me, object ob)
{
	if ( !me ) return;

	if ( !ob ) {
		remove_call_out("finish");
		call_out("finish", 0, me, ob);
		return;
	}

	message_vision(YEL"\n$n�Դ�Ƭ�̣����Ǵ�ʯ����ѹ��������֪��$N����֧�ŵ�ס����������Ӵ�\n"+
			"ʯ�������Ծ��ɽ�£�Ҫȥǣ����ţ��\n\n"NOR, me, ob);

	remove_call_out("wait3");
	call_out("wait3", 5, me, ob);
}

void wait3(object me, object ob)
{
	if ( !me ) return;

	if ( !ob ) {
		remove_call_out("finish");
		call_out("finish", 0, me, ob);
		return;
	}
	message_vision(YEL"\n$n�߹�ȥ��ţǣ�ߣ�������Ծ�µ�����������$N����ߡ�\n\n"NOR, me, ob);

	remove_call_out("finish");
	call_out("finish", 1, me, ob);
}

void finish(object me, object ob)
{
	//object nongfu;
	delete("ppl");

	if ( !me && ! ob) return;

	if ( !ob && me ){
		me->start_busy(-1);
		message_vision("ũ��֪ȥ��$N�����е��ۣ��ͷ�����ʯ�顣\n"NOR, me);
		return;
	}
	if ( !me && objectp(ob))
		return;
   //�����������Կ�
   /*
	if (me->query_temp("nqg/askyingok"))
    {
	   if (!objectp(ob))
	    {
			ob=new("d/dali/yideng/npc/gengzi");
			ob->move(environment(me));
	    }
		tell_object(me,"ũ�򡸺ٺٺ١���Ц�˼�����\n ");
		
		tell_object(me,"\n\n��������������Ʒ����ͦ�ã�����������ô�����Ƶģ���Ȼ��һ����ò��Ȼ�����ӣ�\n");
		tell_object(me,"\n\n ��С�ӣ����治������Ȼ�����ĺ������Ǳ����˹�����\n");
		tell_object(me,"\n\n�������ɣ�");
		tell_object(me,HIR"\n\n\n���ũ��֪������ʲô�裬���㿪ʼʹ�º��֣�\n"NOR);
		ob->kill_ob(me);
		me->start_busy(-1);
		message_vision(HIY"\n\n\n\$N�ۼ�����Σ������æ�˹�����ʯͷ�Ʒ�����$n����������\n", me,ob);
		me->kill_ob(ob);
		
		call_out("check_jiaozi",1,me);
		return ;
    }
     else {
		 */
		me->set_temp("yideng/nongfu_pass", 1);
		message_vision(CYN"\n$n˫����ס��ʯ�������˾���ͦ���ʯ����$N˵��������л���������ȥ�ɡ���\n"NOR, me, ob);
		me->start_busy(-1);
		return ;	
	//}
	
	return;
}

int valid_leave(object me, string dir)
{
	if ( dir == "east" 
	&& !me->query_temp("yideng/nongfu_pass")) {
		if ( present("nong fu", environment(me)))
			return notify_fail("һλũ����Ŵ�ʯ�飬��ס�����ȥ·��\n");
		else
			return notify_fail("һ���ʯ����ס�����ȥ·��\n");
	}
	return ::valid_leave(me, dir);
}
int check_jiaozi(object me)
{
	object nongfu;
	
	nongfu=present("nong fu",environment(me));
    if (objectp(nongfu)&& me->is_fighting(nongfu))
    {
		remove_call_out("check_jiaozi");
		call_out("check_jiaozi",2,me);
		return 0;
    }
	if (!objectp(me)) return 0;
	
	me->set_temp("yideng/nongfu_pass", 1);

	message_vision("�����һ�������������װ�����˹�����ʯͷ�Ʒ����ҵ���ǰ���ĵ�·��\n", me);
	return 1;
	

}