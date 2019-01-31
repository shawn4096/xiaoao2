//bingdong.c ����
//cre by sohu@xojh

#include <ansi.h>
inherit ROOM;
int do_sa(string arg);

void create()
{
        set("short", HIW"����"NOR);
        set("long", @LONG
����һ��С�����������������Ұ��ʱΪ֮һ��������Լ�����˸�
���ܷ�ԲԼ��ʮ�����ҵ����ӣ����ǿ���������ƺ��а׾����Ķ���
���䶯����ϸһ��ȴ��һ�����С��˶��ں�����ǣ�������ɽ��ļ�
��֮�ء�
LONG
        );
        set("exits", ([
          "out" : __DIR__"shanao",
       //   "northwest" : __DIR__"tsroad1",
        ]));

        set("indoors", 1);

        set("coor/x",-10);
		set("coor/y",50);
		set("coor/z",0);
		setup();
}
void init()
{
	object me=this_player();
	add_action("do_search","search");
	add_action("do_sa","sa");
	add_action("do_fang","fang");
	add_action("do_ran","ran");
	add_action("do_xiulian","xiulian");
}

//�����
int do_sa(string arg)
{
	object liuhuang;
	object me=this_player();
	
	if (arg=="���"||arg=="liuhuang"||arg=="liu huang")
	{
		if (!objectp(liuhuang=present("liu huang",me)))
		{
			return notify_fail("������û����ǣ�\n");
		}
		message_vision(YEL"$NС�ĵ��ڵ��Ͻ��������һ��ԲȦ��\n"NOR,me);
		liuhuang->move(environment(me));
		me->set_temp("bingcan/saliuhuang",1);
		return 1;
	}else return notify_fail("��Ҫ��ʲô��\n");

}
int do_fang(string arg)
{
	object hulu;
	object me=this_player();
	
	if (arg=="���«"||arg=="hulu"||arg=="��«")
	{
		if (!objectp(hulu=present("hulu",me)))
		{
			return notify_fail("������û�д���«��\n");
		}
		message_vision(YEL"$N����«С������ŵ�����ϣ���«�ڳ��ڶ��š�\n"NOR,me);
		hulu->move(environment(me));
		me->set_temp("bingcan/fanghulu",1);
		return 1;
	}else return notify_fail("��Ҫ�ڵ��Ϸ�ʲô��\n");

}
int do_search(string arg)
{
	object muding;
	object me=this_player();
	if (!arg ||(arg!="����"&&arg!="bingcan"))
	{
		return notify_fail("���ͷ���Ե���Ϲ��ʲô��\n");
	}
	if (me->is_busy())
	{
		return notify_fail("������æµ�У��޷�����Ѱ�ұ��ϣ�\n");

	}
	if (!me->query_temp("bingcan/askxiu"))
	{
		return notify_fail("�����˰��죬����һ�ֱ�ѩ���ࡣ\n");
	}
	if (!objectp(muding=present("shenmu wangding",this_object())))
	{
		return notify_fail("�˵�û����ľ������\n");
	}
	if (muding->query_temp("dianxiang")<3)
	{
		return notify_fail("��ľ����û�б����㣬���ܷ���ҩЧ��\n");
	}
	message_vision(HBYEL+HIW"$N����ľ������ҩ���Ѿ�����ȼ�����ĵض���һ�߹۲졣\n"NOR,me);

	if (random(me->query("kar"))>25)
	{
		message_vision(HIC"��Ȼ�䣬$N�����ֱ����ڴ���һ��ϤϤ������������$N��æ��ס��Ϣ��һ������ſ���Ķ�!\n"NOR,me);
		me->start_busy(15);
		call_out("do_wait",5+random(10),me);

		
	}else {
		message_vision(HIG"����������ҩ��Ʈ������ĸ�������\n"NOR,me);
		
	}
	return 1;
}

int do_wait(object me)
{
		object obj;
		int j;
		j=me->query_skill("force",1);
		message_vision(HIW"��Ȼ$Nֻ������������������Ѱ���������м�����һ��������Ż���ȳ���$N��Ϣ����\n"+
						"ֻ�����ݷֿ���һ��������µĴ�������������������ͷ�������Σ�ͷ���ϸ߸�����\n"+
						"һ������͹͹�������������߳汾�٣���������Щ��״����������δ���������ε�ľ\n"+
						"��֮�ԣ��ƶ�����ת���������������ɣ������ֱۣ������ý�ľ��֮�У����ŵ�\n"+
						"���ϼ�ľ����Ϣ��һ�ž�ͷס��ȥײ�Ƕ���\n"NOR,me);
			
			obj=new("/d/sld/npc/dushe");
		    obj->set("combat_exp", me->query("combat_exp")*2);
		    obj->set("max_qi", me->query("max_qi")*4);
		    obj->set("eff_qi", me->query("max_qi")*4);
		    obj->set("qi", me->query("max_qi")*4);
		    obj->set("max_jing", me->query("max_jing"));
		    obj->set("jing", me->query("max_jing"));
		    obj->set("eff_jing", me->query("eff_jing"));
		    obj->set("eff_jingli", me->query("eff_jingli"));
		    obj->set("max_neili", me->query("max_neili"));
		    obj->set("jing", me->query("max_jing"));
		    obj->set("jingli", me->query("max_jingli"));
		    obj->set("neili", me->query("max_neili")*3/2);
		    obj->set("jiali", 200);
		    obj->set("str", me->query("str")*2);
		    obj->set("con", me->query("con")*2);
		    obj->set("dex", me->query("dex")*2);
		    obj->set("int", me->query("int")*2);
		    obj->set_skill("unarmed",j +random(50));
		    obj->set_skill("force",j + random(50));
		    obj->set_skill("dodge",j + random(50));
		    obj->set_skill("parry",j + random(50));
			obj->set("no_get",1);
		    obj->move(environment(me));
		    obj->set_leader(me);
		    obj->kill_ob(me);
		    message_vision(RED"$Nһ��ҧ��$n��\n"NOR,obj,me);
			me->start_busy(1);
			return 1;
}

int do_ran(string arg)
{
	object obj;
	object me=this_player();
	if (arg!="��Ѫ") return notify_fail("��Ҫ��ȼʲô��\n");
	if (me->query_temp("bingcan/ranshexue"))
	{
		return notify_fail("�㷽�Ÿոյ�ȼ����Ѫ��������ȼ�����о�quit������\n");
	}
	if (objectp(obj=present("corpse",environment(me)))&&obj->query("kill_by")==me)
	{
		message_vision(HIC"$N����������ɱ������Ѫ���뵽��ľ����֮�У���ҩ��������£�����һ���������ζ��\n"NOR,me);
		me->set_temp("bingcan/ranshexue",1);
		me->start_busy(8);
		call_out("bingcan_come",3+random(5),me);
		return 1;
	}
	else {
		//message_vision(HIC"$N����������ɱ������Ѫ���뵽��ľ����֮�У���ҩ��������£�����һ���������ζ��\n"NOR,me);
		return notify_fail("����ô������ɱ����ô��������Ѫ��\n");
	}
}
int bingcan_come(object me)
{
	object obj,hulu;
	message_vision(HIR"���ڴ�ʱ��������һ�󺮷�Ϯ�壬ֻ��������һ���������˹�������̼�㽽������ǰ��\n"
						"һ��������է�����ԭ�����ǻ��ߣ�ȴ�ǲݴ�����ʲô�������������������������ݽ���\n"
						"ͬʱ����Խ��Խʢ��$N�˺��˼�����ֻ���ݴԿݽ��Ļ�������ľ����ȴ��һ����������"+HIW"�ϳ�"HIR"��\n"NOR,me);
	message_vision(HIG"\n\n��ϳ洿������΢����ɫ����Ѱ���϶�����һ�����࣬����һ����򾣬����͸��ֱ��ˮ��\n"+
						"��ˮ���϶�Ѹ���쳣��������ľ������һ·�������У�����һ�����ȵ�̿��һ�㣬����ľ����\n"+
						"�ļ����������ճ���һ�����ߣ���������ͷ�ԵĶ��ң�˱����Һ����̼����ӱ��ʹ��˲��٣�\n"+
						"ԶԶ��ȥ��������һ��ˮ��ƿ��װ��������ɫ��֭Һ��\n"NOR,me);
	if (!me->query_temp("bingcan/saliuhuang")||!me->query_temp("bingcan/fanghulu")||!objectp(present("hulu",environment(me)))||!objectp(present("liu huang",environment(me))))
	{
		message_vision(HIY"\n\n���Ϸǳ����������������ڸ����������ܻض��С�\n$N�������Ҳû�ҵ�����\n"NOR,me);
		me->delete_temp("bingcan");
		return 1;
	}
	message_vision(HIG"���ϼ�æ��ת�����Ѿ����뵽$N��ǰ���õ����ҩ��֮�У������ͻ�����ó��ڡ�\n�ۼ�һ����«�����ö�����������ٿ��һ�����뵽�Ǹ���«��ȥ��\n"NOR,me);
	obj=new("d/xingxiu/obj/bingcan");
	
	//obj->move(environment(me));

	hulu=present("hulu",environment(me));
	hulu->set("bingcan",1);
	obj->move(hulu);
	me->set_temp("bingcan/bingcanok",1);
	me->set("quest/xx/csz/bingcan/hulu",1);

	return 1;
}
//�����«��

int do_xiulian(string arg)
{
	object hulu,obj;
	object me=this_player();
    if (!me->query_temp("bingcan/bingcanok"))
    {
		return notify_fail("��Ҫ�����������±�������\n");
    }
	if (arg!="���϶���")
	{
		return notify_fail("�������Ǿ綾֮���Ҫ����ʲô��\n");
	}
	if (me->query_skill("huagong-dafa",1)<450)
	{
		return notify_fail("��Ļ����󷨹���̫��������450���ֿ���ס�⺮����Ϯ\n");
	}
	if (me->query_skill("poison",1)<200)
	{
		return notify_fail("��Ķ��Ʋ���200,̫�����ֿ���ס�⺮����Ϯ\n");
	}
	if (time()-me->query("quest/xx/csz/bingcan/time")<86400)
	{
		return notify_fail("������̫Ƶ���ˣ��������۹��࣬�����岻�ˡ�\n");
	}
	if (me->query("quest/xx/csz/bingcan/pass"))
	{
		me->set("title",HBWHT+HIG"���϶��ƴ���"NOR);
		me->set("mytitle/quest/bingcantitle",HBWHT+HIG"���϶��ƴ���"NOR);
		return notify_fail("���Ѿ��⿪����϶��Ƶİ����ˣ���ʲô��Ц\n");
	}
	if (me->query("quest/xx/csz/bingcan/hulu"))
	{
		message_vision(HIC"$N����ָ�أ����������������˲��ع�أ�һ����͵͵��ȥ��ˣ���������ӵ����˰��죬\n"
							+"������Ӵ˲������ˡ����Ӵ�����ɽ�����������Ľ����������̫Ҳ��֪�ô�����������\n"
							+"�Դ���һƬ���ġ�������ȥ���㻹��ʲô��Ϣ�������Ի�ǰ;��˭Ҳ�����������㡣\n"NOR,me);
		if (!objectp(hulu=present("hulu",me)))
		{
			return notify_fail("������û�к�«װ�ر��ϣ������ֿ��ٵ��ӵ��ˣ�\n");
		}
		message_vision(HIW"��$N����߶֮�У���Ȼһ���׹�������һ��������������$N�ĺ�«��ȥ��\n"NOR,me);
		message_vision(HIW"��«����˲�����һ���,$N�������������ǣ�����ֱ����¡�\n"NOR,me);

		hulu->set("bingcan",1);


	}
	if (!objectp(hulu=present("hulu",me))||!hulu->query("bingcan"))
	{
		return notify_fail("������û�к�«���«�еı����Ѿ����!\n");
	}
	message_vision(HIW"$N����˫��һͦ����ת���ӣ��Դ��ӿ������������ץ�㣬���������«�ڣ�ͻȻʳָ����΢΢һ��\n"+
						"һ�ɺ������Ʊ�����ѭ���ֱۣ�Ѹ�����׵��������ţ�$N����Ĭ���ڹ��ھ����ǵ�����������˳��\n"+
						"������������磬��ָ���ۣ������ظ�����ͷ����ϸ������֮���溮���ǡ�\n"NOR,me);
	me->receive_wound("jing",2000,"���溮��");
	me->receive_wound("qi",3000,"���溮��");

	me->apply_condition("cold_poison",10);
	me->add_busy(20);
	if (random(me->query("kar"))>23)
	{
		me->set("quest/xx/csz/bingcan/over",1);
		me->delete_temp("bingcan");
		message_vision(HIY"����������ͨ�����㾭����ó����ֿ����϶��������Ͻ���ȥ�����̹֮�����ת�����ɡ�\n"NOR,me);
	}else {
		message_vision(CYN"\m�������϶�ʧ�ܣ������������ٽ�������\n"NOR,me);
		me->set("quest/xx/csz/bingcan/time",time());
		me->add("quest/xx/csz/bingcan/fail",1);
		me->delete_temp("bingcan");
	}
	return 1;
}

