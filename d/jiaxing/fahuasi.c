// /u/beyond/hz/lingyinsi.c ������
#include <ansi.h>
inherit ROOM;
int do_fail(object me);
int clear_here();

void create()
{
        set("short",HIY"������"NOR);
        set("long", @LONG
�������ǿ����ٰ��Ǹ�����һ����ɲ�������ֽ�ľ��ʦ�¸�����
�˵����Ϊ��ʢ��������������������Ը���ﲻ�����ſڰڷ���һ
���޴�Ļ�ֽͭ��(tonggang)��ͬʱ�ſ�����һ��ͭ��(zhong)���Ա�
ƽʱ���ʱ���졣
LONG
        );
        set("exits", ([
            "northeast" : __DIR__"xiaojing1",
           //"east" : __DIR__"qsddao3",
            
		]));
		set("objects", ([ 
					"d/jiaxing/npc/jiaomu" : 1,
					"d/jiaxing/obj/tonggang" : 1,
		 ]) );

        setup();
}
int init()
{
	
	object me,obj;
	me=this_player();
	if (me->query_temp("quest/���Ӣ�۴�/�����߹�/askkumu"))
	{
		
		message_vision(HIR"��ս��ž����������ƺ���Ů������Щģ��������ȷ�ϣ�\n"NOR,me);
		message_vision(HIC"\n����һ�ᣬ����Ӳ����ѯ������ɮ!\n"NOR,me);
		me->set_temp("quest/���Ӣ�۴�/�����߹�/findfahuasi",1);
		me->delete_temp("quest/���Ӣ�۴�/�����߹�/askkumu");
		return 1;
	}
	//add_action("do_ju","ju");
	if (me->query_temp("quest/���Ӣ�۴�/�����߹�/yanyukillbing")||me->query("quest/���Ӣ�۴�/�����߹�/yanyukillbing"))
	{
		message_vision(HIC"$Nһ�����ű���������˼ƻ��Ը��Լ�������ƽ�����޽��֮�飬����������ţ�Բ��˫�ۣ�ŭ���ɶ���\n"NOR,me);
		if (!present("ke zhene",this_object()))
		{
			obj=new("d/jiaxing/npc/kezhene");
			obj->move(this_object());
		}
		if (!present("zhu cong",this_object()))
		{
			obj=new("d/jiaxing/npc/zhucong");
			obj->move(this_object());
		}
		if (!present("han baoju",this_object()))
		{
			obj=new("d/jiaxing/npc/hanbaoju");
			obj->move(this_object());
		}
		if (!present("nan xiren",this_object()))
		{
			obj=new("d/jiaxing/npc/nanxiren");
			obj->move(this_object());
		}
		if (!present("zhang asheng",this_object()))
		{
			obj=new("d/jiaxing/npc/zhangasheng");
			obj->move(this_object());
		}
		if (!present("quan jinfa",this_object()))
		{
			obj=new("d/jiaxing/npc/quanjinfa");
			obj->move(this_object());
		}
		if (!present("han xiaoying",this_object()))
		{
			obj=new("d/jiaxing/npc/hanxiaoying");
			obj->move(this_object());
		}
		add_action("do_zhuang","zhuang");
		me->delete_temp("quest/���Ӣ�۴�/�����߹�/yanyukillbing");
		me->set_temp("quest/���Ӣ�۴�/�����߹�/fhscome2",1);
	}
	//�ڴ˱�����Լ
	add_action("do_bisai",({"bisai","dadu","duyue","du"}));
	return 1;
}
int valid_leave(object me, string dir)
{
	if (!wizardp(me) 
		&& objectp(present("tong gang", environment(me))) 
		&& !me->query_temp("quest/���Ӣ�۴�/�����߹�/jugang")
		&&	dir == "northwest")
		return notify_fail("���ܾ��������뿪����̫�ã�Ҫ�ٸ��ص�Ķ��������ſɣ��ϲ������˶Է�ʿ����\n");
	return ::valid_leave(me, dir);
}

int do_zhuang(string arg)
{
	object me,gang;
	me=this_player();
	if (!arg||arg!="zhong")
	{
		return notify_fail("��Ҫײʲô��\n");
	}
	if (!objectp(present("jiaomu dashi",environment(me)))) 
		return notify_fail("��ľ��ʦ���ڴ˵أ��������ײ��Ҳû�ã�\n");
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/fhscome2"))
		return notify_fail("������ľ׮ײ����ӣ���������������,���쳿��ĺ������\n");
	
	if (!objectp(gang=present("tong gang",me))) 
		return notify_fail("������ľ׮ײ����ӣ�����������������\n");
	
	message_vision(HIR"\n$N������ͭ�ף�������ײ��������ŵ��ǿ����ӣ�����֮�£�ͭ���ѳ������ѿڡ�\n"
				   HIC"\n\n�����߹ֲ�֪$N����Ҳ�����һζ��������֮�ˣ�ֻ��������׷Ѱ����²��ã�\n"
					"ŭ�����վ���������ƽ�����޽��֮�飬���Լ���һ���߹�ȴ�����������ˣ�����\n"
					"��������һ����$N����Խʢ���߹�Խ�ǲ������ã�����$Nֻ�Ǹ�����֮�����������ڷ�˵�ˡ�\n"NOR,me);
	call_out("qg_fight1",2+random(4),me);
	me->set_temp("quest/���Ӣ�۴�/�����߹�/zhuangzhong",1);
	me->delete_temp("quest/���Ӣ�۴�/�����߹�/fhscome2");

	return 1;
}
int qg_fight1(object me)
{
	object han,ying;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("�������ӣ��������߹ִ�ܣ���������������ϣ�\n");
	}
	message_vision(CYN"�����ԶԺ�СӨ˵���������ã��������ϡ���\n"NOR,me);
	if (!objectp(han=present("han baoju",this_object())))
	{
		han=new("d/jiaxing/npc/hanbaoju");
		//han->set_super(me);
		han->move(this_object());
	}
	han->kill_ob(me);
	if (!objectp(ying=present("han xiaoying",this_object())))
	{
		ying=new("d/jiaxing/npc/hanxiaoying");
		//han->set_super(me);
		ying->move(this_object());
	}
	ying->kill_ob(me);
	call_out("qg_fight2",3+random(4),me);
	return 1;

}
int qg_fight2(object me)
{
	object nan,zhang;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("�������ӣ��������߹ִ�ܣ���������������ϣ�\n");
	}
	message_vision(HIG"\n\n����һ����$N������СӨ������������Կ��졣�������죬$N���ָ��죬������ͭ��\n"
					"��ס�����ԵĽ����ޣ������������죬Ӳ��Ӳ�ã�Ҫǿ�ж�ȡ��СӨ���г�����Ƭ��֮�䣬\n"
					"��СӨٿ�����У����Ƶ��˵��˷���֮�ԡ�\n"NOR,me);
	message_vision(CYN"\n\n�Ű�������ɽ������ϣ�ʱ˴˿���һ�ۣ��ȵ������֡���\n"NOR,me);

	if (!objectp(nan=present("nan xiren",this_object())))
	{
		nan=new("d/jiaxing/npc/nanxiren");
		//han->set_super(me);
		nan->move(this_object());
	}
	nan->kill_ob(me);
	if (!objectp(zhang=present("zhang asheng",this_object())))
	{
		zhang=new("d/jiaxing/npc/zhangasheng");
		//han->set_super(me);
		zhang->move(this_object());
	}
	zhang->kill_ob(me);
	call_out("qg_fight3",3+random(4),me);
	return 1;
}
int qg_fight3(object me)
{
	object zhu,quan;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("�������ӣ��������߹ִ�ܣ���������������ϣ�\n");
	}
	message_vision(HIC"\n\n��ϼ������������֣�أ�Դ����·磬��ȫ��һ���֣����˴����๥����ȥ��\n"NOR,me);
	message_vision(CYN"\n\n�Ű�������ɽ������ϣ�ʱ˴˿���һ�ۣ��ȵ������֡���\n"NOR,me);

	if (!objectp(zhu=present("zhu cong",this_object())))
	{
		zhu=new("d/jiaxing/npc/zhucong");
		//han->set_super(me);
		zhu->move(this_object());
	}
	zhu->kill_ob(me);
	if (!objectp(quan=present("quan jinfa",this_object())))
	{
		quan=new("d/jiaxing/npc/quanjinfa");
		//han->set_super(me);
		quan->move(this_object());
	}
	quan->kill_ob(me);
	call_out("qg_fight4",3+random(4),me);
	return 1;
}
int qg_fight4(object me)
{
	object ke;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("�������ӣ��������߹ִ�ܣ���������������ϣ�\n");
	}
	message_vision(HIC"\n\n�������������������˲��ᣬͦ�����ȣ���Ҫ��ǰ��ս��ȫ�𷢽е�������磬������ɣ�\n"
					"�򡮽���λ���ٴ�С������������δЪ������������������һǰһ����$Nü�����ҿ�ɵ�����\n"NOR,me);
	//message_vision(CYN"\n\n�Ű�������ɽ������ϣ�ʱ˴˿���һ�ۣ��ȵ������֡���\n"NOR,me);

	if (!objectp(ke=present("ke zhene",this_object())))
	{
		ke=new("d/jiaxing/npc/kezhene");
		//han->set_super(me);
		ke->move(this_object());
	}
	ke->kill_ob(me);
	message_vision(HIG"\n\n���������һ���������������ܵĽк��������˷�������Ȼ���������ˡ�����ʱȫ������Խ��Խ�ᣬ\n"
						"�����в�ס���ź�����������ʹ���ң����Ű�������һ�Բ�������֪������Ρ�ֻ��ȫ�𷢵���\n"
						"���򡭡��򡭡���������ͬ�ˡ�������������ȴ�ǲ����ԣ�˫��һ���ö����һ��ɳ�����ö�ִ�ͬ�ˡ�\n"
						"֮�ҵġ��ڡ�λ������λ��������ö�ִ�ͬ�ˡ�֮��ġ��ᡯλ�����롯λ��\n"
						"\n\n$N�����һ�󲽣��ܿ��ˡ�ͬ�ˡ��Ĳ�λ��û�ϵ�������ͻȻ�üƣ�ֻ��������ͬʱ������\n"
						"�Ҽ�����һ�⣬�����׼����λ������һ�⣬ȴ���ں�СӨ���ġ�������־���ϲ���ȵ��������ã���������\n"NOR,me);
	me->apply_condition("heixue_poison",20);
    message_vision(HBCYN+HIB"\n\n$Nһʱ������Ϊ����������У�\n"NOR,me);
	call_out("qg_fight5",3+random(4),me);
	return 1;
}
int qg_fight5(object me)
{
	object jiaomu;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("�������ӣ��������߹ִ�ܣ���������������ϣ�\n");
	}
	message_vision(HIC"\n\n�����е��������׽�Ͷ�����ٰ���Ƭ�̣���������������\n"
					"$N֪��������ⰵ�����ж�����\n"NOR,me);
	


	message_vision(HIG"\n\n$N�����Ƕ�ɮ�������ٱ����ᣬ�����Ѳظ�Ů����Ϊ���֮���������߹ּ�����һ�������\n"
						"��������Ҳ�ز�ȷ����ĳ�����������ڣ������������ϥ�����³����Ӷ�������ɱ�������ϱ˴˶�����\n"
						HIR"\n\n�����һֱ���ڵؽ�֮�У�����ɮ˵�භ˫���������˵��أ������ǲ�ʤ֮ϲ����ľ����֮�࣬\n"
						"�������Ҫ�������ˣ������е�����������������������\n"
						HIG"����¹�����Ц��������Ҫ�ҷ��µ��ӣ����������سɷ�ô����������������$N���ű㿳��\n"
						"��ľŭ��������ƽ��֮����������һ���ڽ�ľͷ��׼�������ȥ����������Ӽ��࣬�����书ʵ��̫�\n"
						"û�ܱܿ�����ν�ľ���������֮�ϣ���ʱײ�����������ݡ�������ۼ������Դ󷢣�Ҳ���˽�ľ���Լ��ж���\n"
						"�ٵ�������ͷ�Ͽ��䣬վ�������Ե�Сɳ�ֺ�����ס���ұۣ���һ��ȥ�������졣�����ŭ�����ص�������\n"
						"Сɳ�ֿ����ڵء�\n"
						HIY"\n\n��Ƽ��У�����������ס�֣���������������˶������ӣ������Ż�ɱ����Ϊ�򱨳���ʱ����������Ѫ��\n"
						"�����������ɱ�ˣ���Ҳ���Ͳ�ס����������ȥ�����˴�\n"
						HIC"\n\n������۾�Ϲ�ˣ������ر�������һ��������֮������֪��Ů�ӣ�̾��������ľ���У����Ƕ����㺦������\n"
						"������������Ů�ˣ���\n"
						HIR"\n\n��ľһ������ʱ���������Լ�һʱ���죬�������������������г��������ѣ������ּ���˫���ڵ���һ�ţ�\n"
						"��������˫�ֻ��ţ�����������ȥ������¼��������Ͷ񣬴󺧱ܿ�����ľ���˺������ͣ�����һͷײ�ڴ�\n"
						"�����ϣ��Խ����ѣ���ʱ������������ŵĻ겻���壬���ﻹ��ͣ����������Ƽ��������������Ƽ��У�����������\n"
						"�Ҳ�ȥ��������������������Խ��ԽԶ��\n"NOR,me);
	if (objectp(jiaomu=present("jiaomu dashi",this_object())))
	{		
		jiaomu->die();
	}
	me->set("quest/���Ӣ�۴�/�����߹�/�����¼�ս",1);

	me->set_temp("quest/���Ӣ�۴�/�����߹�/fhsfight7g",1);
	return 1;
}
//��ı���

int do_bisai(string arg)
{
	object me,ke,zhu,han,nan,zhang,quan,ying;
	me=this_player();
	if (!arg||arg!="�����߹�")
	{
		return notify_fail("��Ҫ��˭��ģ�\n");
	}
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/fhsfight7g"))
	{
		return notify_fail("��Ե�޹ʣ���Ҫ��˭��ģ�\n");

	}
	if (me->is_busy()||me->is_fighting())
	{
		return notify_fail("������æµ����Ͼ���ģ�\n");

	}
	if (!objectp(ke=present("ke zhene",this_object()))) 
	{
		do_fail(me);
		return notify_fail("��Ƣ�����꣬��������Ϊ��ʧ��ɱ��������ʧ�ܣ�\n");
	}
	if (!objectp(zhu=present("zhu cong",this_object())))
	{
		do_fail(me);
		return notify_fail("��Ƣ�����꣬������Ϊ��ʧ��ɱ��������ʧ�ܣ�\n");
	}
	if (!objectp(han=present("han baoju",this_object())))
	{
		do_fail(me);
		return notify_fail("��Ƣ�����꣬���������Ϊ��ʧ��ɱ��������ʧ�ܣ�\n");
	}
	if (!objectp(nan=present("nan xiren",this_object())))
	{
		do_fail(me);
		return notify_fail("��Ƣ�����꣬�����ϣ��Ϊ��ʧ��ɱ��������ʧ�ܣ�\n");
	}
	if (!objectp(zhang=present("zhang asheng",this_object())) )
	{
		do_fail(me);
		return notify_fail("��Ƣ�����꣬����Ű���Ϊ��ʧ��ɱ��������ʧ�ܣ�\n");
	}
	if (!objectp(quan=present("quan jinfa",this_object())) )
	{
		do_fail(me);
		return notify_fail("��Ƣ�����꣬���ȫ��Ϊ��ʧ��ɱ��������ʧ�ܣ�\n");
	}
	if (!objectp(ying=present("han xiaoying",this_object())))
	{
		do_fail(me);
		return notify_fail("��Ƣ�����꣬�����СӨΪ��ʧ��ɱ��������ʧ�ܣ�\n");
	}
	if (!living(ke)) return notify_fail("�Ȱѿ����Ū����˵��\n");
	if (!living(zhu)) return notify_fail("�Ȱ����Ū����˵��\n");
	if (!living(han)) return notify_fail("�ȰѺ�����Ū����˵��\n");
	if (!living(nan)) return notify_fail("�Ȱ���ϣ��Ū����˵��\n");
	if (!living(zhang)) return notify_fail("�Ȱ��Ű���Ū����˵��\n");
	if (!living(quan)) return notify_fail("�Ȱ�ȫ��Ū����˵��\n");
	if (!living(ying)) return notify_fail("�ȰѺ�СӨŪ����˵��\n");
	me->start_busy(30);
	
	me->set("quest/���Ӣ�۴�/�����߹�/dadu",1);
	
	message_vision(HIC"$N������������������������ӣ�ʱ�����ϵó�Щ�����Ƕĵ�ȴ���湦���汾�£����ǵ���һʱ��Ѫ��֮�¡�\n"
					"����ȭ�������Ⱦ�ʤ������ѧ��ĸ������ᡣ���Ƕ��������еĳ�������������������С������������������\n"
					"�����߹ֶ��룺�����õ���ȭ�ž�ʤ����������ô�ַ��ӣ��ѵ������ȺȾƣ���$N��Ȼ�����������������������\n"
					"һ�˶�������λ���������书�����ö����������������ɼ�ı����һ�������������Ҫ������ͷ��������˭����\n"
					"Ӣ������ܡ����ⷬ��ֻ���ý����߹ָ���Ѫ�����š�\n"
					NOR,me);
	call_out("do_bisai1",4+random(4),me);
	return 1;
}
int do_bisai1(object me)
{
	message_vision(YEL"\n\n$N�������Ʊ���Դ������������ˣ���Ϊ����������ĺ��������ô����»��ù���������档�����ǰ���ν�ʶ\n"
					"������ˡ����׷�϶���µľ���˵�ˡ������߹����ڶ��У���ס�ڵ�ʹ����˱�Ű����͢�����޳ܡ�$N���ϣ�\n"
					"˵�������Ƕ���´���ȥ�ģ����ǹ�Х����������ϣ����˿´���뺫�����ã�������λ�����������ˡ�����������\n"
					"���Ҽǵ����������������������ǡ���$N�������ܺá����������ĵ����Ӱ��ϣ�ȴ��֪���ںη����ǰ���ƶ������������\n"
					"��λȴ���ϵá�ƶ�����λ�ĵľ�������¡���˷�����������������СӨ���ŵ�������������ȥ�����ϣ���ȥ�Ȱ��ϣ�\n"
					"˭�ȳɹ�˭ʤ���ǲ��ǣ���\n"
					NOR,me);
	call_out("do_bisai2",4+random(4),me);
	return 1;
}

int do_bisai2(object me)
{
	message_vision(WHT"\n\n$N����������һʮ���꣬�����Ƕ�ʮ�����ˣ��������ڼ��˸�����¥ͷ��ᣬ���������ϵ�Ӣ�ۺú�������һ����\n"
					"�ƺ�����֮�࣬���������ӱ������գ�����ƶ����ͽ�ܸ����أ�����������ͽ���˵ã��������߹���������ƿ����ԡ�\n"
					"$N�ֵ�����Ҫ����λ������ƶ�����ԣ�������ʤһ����Ҳ�������Զ�Ӯ�٣�Ҳû��ô��ʡ������Ұ�ȫ���½̸���һ�ˣ�\n"
					"��λҲ����ҵ����һ�ˡ���������һ��һ�ı��գ���ʱ���ƶ����ͽ�ܵ�ʤ�������ɷǵ��ķ��ڷ����ɡ���\n"
					HIR"\n\n���������������ܣ����������ڵ���һ�٣��е������ã����Ƕ��ˡ���\n"NOR,me);
	call_out("do_bisai3",4+random(4),me);
	return 1;
}

int do_bisai3(object me)
{
	message_vision(HBYEL+HIW"\n\n��ϲ�㣬������ɡ����Ӣ�۴���֮�������߹֡��½ڣ�\n"NOR,me);
	message_vision(HBYEL+HIW"\n\n�����ڴ���һ�½ڡ���Į��ɳ���ľ�����ڣ�\n"NOR,me);

	me->set_temp("quest/���Ӣ�۴�/�����߹�/over",1);
	me->set("quest/���Ӣ�۴�/�����߹�/over",1);
	me->set("quest/���Ӣ�۴�/time",time());
	clear_here();
	return 1;
}
//ʧ�ܺ���
int do_fail(object me)
{
	if (!me)
	{
		me->delete_temp("quest/���Ӣ�۴�/�����߹�");
		me->set("quest/���Ӣ�۴�/time",time());
		me->add("quest/���Ӣ�۴�/fail",1);

		return notify_fail("�����б�ɱ��ʧ�ܣ�\n");
	}
	if (!living(me))
	{
		me->delete_temp("quest/���Ӣ�۴�/�����߹�");
		me->set("quest/���Ӣ�۴�/time",time());
		me->add("quest/���Ӣ�۴�/fail",1);
		clear_here();
		return notify_fail("�����б����Σ�ʧ�ܣ�\n");
	}
	return 1;
}

int clear_here()
{
	object ke,zhu,han,nan,zhang,quan,ying;

	if (objectp(ke=present("ke zhene",this_object()))) 
	{
		destruct(ke);
	}
	if (objectp(zhu=present("zhu cong",this_object())))
	{
		destruct(zhu);
	}
	if (objectp(han=present("han baoju",this_object())))
	{
		destruct(han);
	}
	if (objectp(nan=present("nan xiren",this_object())))
	{
		destruct(nan);
	}
	if (objectp(zhang=present("zhang asheng",this_object())) )
	{
		destruct(zhang);
	}
	if (objectp(quan=present("quan jinfa",this_object())) )
	{
		destruct(quan);
	}
	if (objectp(ying=present("han xiaoying",this_object())))
	{
		destruct(ying);
	}

	return 1;
}