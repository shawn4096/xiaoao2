// /area/jiangbei/wudang/zixia.c ������
// By River@SJ

inherit ROOM;
#include <ansi.h>
int do_heal(string arg);
int zhao_come(object me,object zsf);
int check_fight(object me,object asan);
//check_fight(me,zsf,asan);	

void create()
{
        set("short", HIW"������"NOR);
        set("long", @LONG
��ģ������ư�������������������䵱ɽչ����¡�����Ⱥ��ɽ�뻷
�ƣ����ִ������������ţ��������ˣ���������Ϊ���������ء���������
��������������䡣�λ�����٥һ�����Σ��μ��ˡ����񡱣���һ��ʿΪ��Բ
�Σ�˵Ҫ��ˮ���Ϸ�ѹ�򣬲������ǡ�����ѡ������ʮ������֮һ���䵱ɽ��
��չ�����Ϊˮ�����佨��������������Ͷ����Ԫʥ������ 
LONG
        );

        set("exits", ([
                "out" : __DIR__"zxgdamen",
                "southup" : __DIR__"nanyan",
        ]));

        set("no_clean_up", 0);

        set("objects",([
                CLASS_D("wudang")+ "/wanqing" : 1,
                __DIR__"npc/daotong" :2,
        ]));

        set("outdoors", "�䵱");

        setup();
}
void init()
{
	object me=this_player();
	if (!me->query_temp("mwd/start")) return;
	
	if (me->query_temp("mwd/step6")
		&&me->query_temp("mwd/start")
		&&!me->query("mwd/over"))
	{
		me->start_busy(3);
		
		call_out("do_find",2+random(3),me);
		me->delete_temp("mwd/step6");
	}

}
int do_find(object me)
{
		object kongxiang;
		message_vision(HIG"\n\n$N���н��ǣ��첽��ɣ��������ܵ�С��ʿ���ƺ����ڸ���æµ���ƺ��������ѻ�û�з��������в��ɴ󶨡�\n\n"
							+"����$N���߼䣬��Ȼ����ǰ��һλ����ɮ�����ڴҴұ��ߣ���ɫ�ƺ����ǻ��š�\n"NOR,me);
	    me->delete_temp("mwd/step6");
		if (!objectp(kongxiang=present("kongxiang dashi",this_object())))
		{
		
			kongxiang=new("d/wudang/taiji/kongxiang");
			kongxiang->move(this_object());
			kongxiang->greeting();
		}
		me->set_temp("mwd/step7",1);
		call_out("find_yudaiyan",3+random(3),me,kongxiang);
		return 1;
}
int find_yudaiyan(object me,object kongxiang)
{
	message_vision(HIY"\n\n$N�����ɻ�������һ·��������������������ͨ�������˵���Ա����������࿴�����������ǻ��ŵ����ӡ�\n\n"
							+"����ã��������С��ͯ�Ĳ���£������������Ϳ���̸�˻ᣬ��ɫ���ǽ��ţ��Ը�С��ͯ����̧��ȥ����ʦү��\n"NOR,me);
	call_out("zhang_come",3+random(3),me,kongxiang);	
	return 1;
}
int zhang_come(object me,object kongxiang)
{

	object zsf;
	//object room;
	//room=load_object("d/wudang/houyuan");
	message_vision(HIC"\n\n��յ��⾰��һλ��ü�԰׵��ϵ��˻��������������������ֵĿ�ɽ��ʦ�����ᣡ��\n\n"NOR,me);
	if (!objectp(zsf=present("zhang sanfeng",this_object())))
	{
		zsf=new("kungfu/class/wudang/zhang");
		zsf->move(this_object());
		//zsf->command("chat ....");
	}

	call_out("kx_kill",2+random(3),me,kongxiang,zsf);

}

int kx_kill(object me,object kongxiang,object zsf)
{
	
	message_vision(HIC"\n\n����һ����������������ͨһ���򵹣�������ޡ�\n\n"NOR,me);
	kongxiang->greet2();
	message_vision(HIY"\n\n�������ۼ���������ѹ���Ҳ����̾��һ���������������������������������顣��˵�վ��뽫������������\n"NOR,me);
	message_vision(HIR"\n\n��֪��ʱ������ͻ�䣬�����Ȼ�����Ŀ������һ�������������С��������\n"NOR,me);
	kongxiang->kill_ob(zsf);
	zsf->kill_ob(kongxiang);
	zsf->receive_wound("qi",2000+random(1000),kongxiang);
	zsf->apply_condition("neishang",10);
	me->delete_temp("mwd/step7");
	me->set_temp("mwd/step8",1);
	add_action("do_heal","heal");
	return 1;
}

int do_heal(string arg)
{
	object me=this_player();
	object zsf,kongxiang;
	zsf=present("zhang sanfeng",this_object());
	
	if (objectp(kongxiang=present("kongxiang dashi",this_object())))
	{
		return notify_fail("�������ں�������������������Ҫ��ʲô��");
	}
	if (!objectp(zsf)) return 0;

	if (me->is_fighting() || zsf->is_fighting())
	{
		return notify_fail("���������ں�æ��\n");
	}
	if (!me->query_temp("mwd/step8"))
	{
		return notify_fail("��û��Ī�����������Ϲ���ң���ʲô�ˣ�");
	}
	if (!arg || arg !="������")
	{
		return notify_fail("��ҪΪ˭���ˣ�");
	}
	message_vision(YEL"\n\n$N������𣬽��ִ���������ı����˹�Ϊ�����ˡ�������ֻ��һ���ھ�������������ȵĿ���$Nһ�ۡ�\n"NOR,me);
	message_vision(HIY"\n\n\n��$N��ȫ����ת֮�£�$n���ƴ�Ϊ��ת�����漴������һ����Ѫ��$n��֪������һ����ʵ���˲��ᡣ\n"NOR,me,zsf);
	message_vision(HIR"\n\n$ņͷ����һ��$N����Ц����û�뵽���䵱�ɾ�Ȼ������˸��֣�����˭�����£�\n"NOR,me,zsf);
	message_vision(HIG"\n\n$n˵����$N��һ���������˵ã��������䵱Ҫ�����ˣ�������������\n"NOR,me,zsf);
	message_vision(HIG"\n\n�����ĬȻ������֪ɽ�ϳ���ʦ�����Լ�֮�⣬�������Ĵ����ӵ��书����������������У�\n"
						+"ֻ��ͽȻ����������֮�£�Ω���Լ���ȴһ�����͵��˷�����������ʦ���ܵ����ˣ��պ��ٸ����\n"
						+"�����������������飬��ȥ����Щ��˵���ұ������������������������š��������Ӧ��ȥ�ˡ�\n"NOR,me);
	message_vision(YEL"\n\n������������ʦͽ�ദ�վã�������ͨ��������ô˵����֪���⣬˵��������ң�����ʤ��������黳��\n"
						+"�䵱�ɵľ�ѧȴ��������жϡ�������ʮ���£�������ѧ��Ҫ��һ��̫��ȭ��̫�������˿̱㴫����ա�\n"
						+"�����һ���������Լ��з��Ѿã��ǻ���ѧʲôȭ���������ο���ʱǿ���Ѿ���ۣ�������Ͼ��ϰ�书\n"
						+"ֻ����������ʦ��������˵����ȥ�ˡ�\n"NOR,me);
	message_vision(WHT"\n\n�����ᵭ��һЦ��˵���������䵱����������������������������֮�£��Դ������ԣ��������Դ˶�����\n"
						+"������̫��ȭ��̫��������������ѧ֮��ȫȻ��ͬ�������Ծ��ƶ��������ˡ���ʦ�����������ʹ����ǿ�У���\n"
						+"�����м���û��ϲ�����ڴ�ĺ֮�꣬���������书������Զ�š����ۡ���Ϫ����ͤ�����ȶ�������ߣ�\n"
						+"�����Ĵ�����֮�С��������Ⲣ�޽ܳ��˲ģ��ο���Ҳ����ɽ�ϡ��������������ƽ���յ����Ρ��䵱��\n"
						+"һ�յ����裬�к������ֻ������̫��ȭ�ܴ�����������䵱�ɴ������ܴ�֮ǧ�š���˵�������ɷ��\n"
						+"�������������ƻ�û��ѹ����ǿ�з������ϡ������ΨΨ��Ӧ��������ʦ��Ҫ�Լ����踺�أ��ԽӴ����ɾ���Ϊ��һҪ�塣\n"NOR,me);
	message_vision(CYN"\n\n�����Ỻ��վ��������˫���´����ֱ����⣬��ָ΢�棬����ֿ�ƽ�У���������������������ǰ����۰뻷\n"
						+"������Գ����ƣ����Ʒ��������ƣ�˵����������̫��ȭ������ʽ��������һ��һʽ��������ȥ,�ֿ��н�����ʽ��\n"
						+"���ƣ���ȸβ�����ޡ�������ʽ���׺����ᣬ§ϥ�ֲ�������������������Ʊա�ʮ���֡�������ɽ\n"
						+"$N��ʱ����̫ʦ�����⽫�����ݵ��ر�����ʹ����ҿ��Կ�������������������С��ֻ����á�֮ʱ��ֻ������������������\n"
						+"Ŀ�����������ֱۣ�˫�ƣ�������£������������ɽ��ȴ�������������޼ɶ�Ȼ֮��ʡ�򣺡�����������졢�Ծ��ƶ����ϳ���ѧ\n"
						+"�벻�����侹������˸����Ĺ���$N�书���ͼ��ߣ�һ����ᣬԽ��Խ���񣬵���������˫��Բת��ÿһ�ж�����̫��ʽ�������仯��\n"
						+"��΢���ʵ�ǿ�������ѧ�д���δ�е�����ء���\n"NOR,me);
	message_vision(HIW"\n\n�������������ȭ����Ҫ�����ɷ��ɣ���չδչ�������ⲻ�ϡ�������Ҫ���½�˵��ֻ����ǰ���������ԶԶ����\n"
						HIR+"\n\nһ�������Ƴ������������������ϵ���Ȼ��ͷ���������ǰ���ͽ��ͽ���������ˡ�����һ���ֺ��������������ð���\n"
						+"��һ�ѻ������������˵��������һ����������������������ϵ������Ǳ���������������ס������\n"
						+"�󵽸�������������ʾ�ڣ��ô����������ѧ̩���϶�������ģ������\n"NOR,me);
	
	me->set_temp("mwd/step9",1);
	me->delete_temp("mwd/step8");
	call_out("zhao_come",2+random(3),me,zsf);
	return 1;

}

int zhao_come(object me,object zsf)
{
	object zhao,he,lu,laoda,laoer,laosan;
	if (!objectp(zhao=present("zhao min",this_object())))
	{
		zhao=new("d/city/kedian/zhao");
		zhao->move(this_object());
	}
	
	if (!objectp(he=present("he biweng",this_object())))
	{
		he=new("d/city/kedian/hebw");
		he->move(this_object());
	}
	if (!objectp(lu=present("lu zhangke",this_object())))
	{
		lu=new("d/city/kedian/luzk");
		lu->move(this_object());
	}
	//���󣬰���������
	if (!objectp(laosan=present("a san",this_object())))
	{
		laosan=new("d/wudang/taiji/asan");
		laosan->move(this_object());
	}
	if (!objectp(laoer=present("a er",this_object())))
	{
		laoer=new("d/wudang/taiji/aer");
		laoer->move(this_object());
	}
	if (!objectp(laoer=present("a da",this_object())))
	{
		laoda=new("d/wudang/taiji/ada");
		laoda->move(this_object());
	}
	zhao->greet_zhang();
	laosan->greet_zhang();
	
	message_vision(HIG"\n\n�������������ȻƮȻ�³������µ������������⣬��ת�����룺�������ұ�����ϵ�ƴ�����ܾ��ˣ�\n"
						+"��Ҳ���ʶ����ֵ�ʢ���ˡ���������Ϣ����˫Ŀ��ס�����������ϣ���Ϣ����ת������������������ģ���\n"
						+"����������΢�ı���֮���������־����һ㵣�֪�����Ƿ������ڵ������书��������ڣ��������а������\n"
						+"�ǽ�շ�ħ��ͨ�������������������飬Ҳ���Ȼһ����������������С������֪����̫��ȭ�Ƿ�Ը����ˣ���\n"NOR,me);


	message_vision(HIC"\n\n������������꣬���ܸ���͵Ϯ���ˣ���֪���ܷ�ֿ���ס��λ���֣�"+HIR"���Ƿ�Ը������������ս��douquan����\n"NOR,me);
	
	add_action("do_bishi1","douquan");
	return 1;

}
int do_bishi1()
{

	object me=this_player();
	object asan;
	asan=present("a san",this_object());
	if (!me->query_temp("mwd/step9"))
	{
		return notify_fail("��û��Ī�������������ʲô��ȭ��");
	}
	if (!asan)
	{
		asan=new("d/wudang/taiji/asan");
		asan->move(this_object());
	}
	if (me->query_skill_mapped("cuff")!="taiji-quan"||me->query_skill_mapped("parry")!="taiji-quan")
	{
		return notify_fail("������������̫��ȭȥ����������û�м���̫��ȭ��\n");
	}
	message_vision(HIY"\n\n$N����Ҫ��$n��ǰ��ʾ�䵱�ɵ����磬�˹�����˵��������ʦЪϢƬ�̣����Сë����ͽ�����������ˡ�\n"
						+"Ҳ��������ʶ��ʶ���䵱�ɵ��书��ʡ�����������죬��֪��ԭ���ܡ�\n"NOR,me,asan);
    message_vision(CYN"\n\n��������������֪�����ڹ��˵ã�����΢΢Ц��������Ҳ�ã���Ȼ��λ��շ�ħ�񹦵�Ӣ�����ʶ��ʶ��\n"
						+"���䵱���񼼣��ǾͰ������½������̫��ȭ�İ���˵���������������Ƿ����ڻ��ͨ��\n"NOR,me,asan);
	
	message_vision(HIR"\n\n$N������������ʦ�Ľ��⣬����̫��ȭ�����������һ�㡣\n"	NOR,me);

	asan->fight_ob(me);
	me->fight_ob(asan);

	call_out("check_fight",3+random(3),me,asan);
	return 1;
}

int check_fight(object me,object asan)
{
	if (me->is_fighting(asan))
	{
		remove_call_out("check_fight");
		call_out("check_fight",2,me,asan);
		return 1;
	}
	if (!living(me))
	{
		call_out("fight_fail",1,me);
		return notify_fail("���������Σ�����ʧ�ܡ�\n");
	}
	message_vision(HIC"\n\n$N��$n˵����������ѧ������ȭ��������ʦ�������˶�����Ѫ������������̫��ȭ��������ѧէ����\n"
						+"δ�ؼ�������ȭ���еľ�Ҫ����ʮ��֮�ڣ����²��ܽ����������������ѧ��δ��������\n"
						+"����ȭ�����У���һ����������ס�\n"NOR,me,asan);
	
	message_vision(HIY"\n\n\n�������$N˵���������ⲻ������̫��Բת����ʹ�Ͼ������û����ƣ����������Զϡ�һ��һʽ������ڽ�\n"
						+"�ᴮ���糤����ӣ����ϲ��������������ʲż�$N�ٵ�ʹ�У����ĵ�̫����ζ��ֻ����ԭ���书̫ǿ��\n"
						+"ȭ������Ƿ�����δ�����̫��ȭ�ǡ�Բת���ϡ�֮�⡣\n"NOR,me);
	asan->greet_yu();
	asan->kill_ob(me);
	me->kill_ob(asan);
	call_out("douquan_finish",3+random(2),me,asan);
	return 1;

}
int douquan_finish(object me,object asan)
{

	if (!objectp(me))
	{
		return 0;
	}
	if (!living(me))
	{
		me->delete_temp("mwd");
		call_out("fight_fail",1,me);
		return notify_fail("���վ���̫��ȭ����������Ϊ�����������ָ���ˣ����Բ��ѡ�");
	}
	if (objectp(asan))
	{
		remove_call_out("douquan_finish");
		call_out("douquan_finish",2,me,asan);
		return 1;
	}

	message_vision(HIY"\n\n�������ҵĴ򶷣�$N����������ɱ������ȴ����һ�����յĶ�Թ�������ῴ�����ϲ�����ϣ�����$NԽ��Խ�����͡�\n"NOR,me);
	message_vision(HIY"\n\n�������$N΢΢һЦ���������⺢�����ǲ����������䵱�ɶɹ�Σ��������Ե���Ժȥ������̹���̫��ȭ�İ�������\n"NOR,me);
	
	message_vision(HIG"\n\n��ʱ���������Ⱒ���ȵ�����أ��ͺ������ɸ����ұ�ƴ����ô��"+HIR+"�����ȶ���answer yes��or ������answer no����\n"NOR,me);
	message_vision(HIG"\n\n$N��������ӣ�̫��Ѩ���ݼ��˫Ŀ����⺬�̣�һ�������ڹ���������Ϊ����ľ��磬$N������Ȼ����������һ��������ƴ����������\n"NOR,me);
	//��һս����
	me->set_temp("mwd/step9",1);
	me->delete_temp("mwd/step8");
	me->set_temp("helpwd/fightasan",1);
	me->set("helpwd/fightasan",1);
	add_action("do_answer","answer");
	return 1;	

}

int do_answer(string arg)
{
	object me=this_player();
	object aer;
	int ap,dp;
	
	aer=present("a er",this_object());
	if (!me->query_temp("mwd/step9"))
	{
		return notify_fail("��û��Ī�������������ʲô�һش�ʲô��");
	}
	if (!aer)
	{
		aer=new("d/wudang/taiji/laoer");
		aer->move("d/wudang/zixia");
	}
	
	ap=me->query_skill("force",1)*me->query("neili")/1000;
	dp=aer->query_skill("force",1)*aer->query("neili")/1000;
	if (arg=="yes")
	{
		message_vision(HIC"\n\n�������ȵ����Ҵ��䵱���ڹ��ų����µ�һ����������ս��\n"NOR,me);
		message_vision(HIY"\n\n��ͺͷ����������������Ƽ���$N�ؿ��������Ƽ�δ����$N�Ѿ���Ϣ΢�ϣ�����һ�С�б��ʽ����\n"
					+"����������ƫ����ͺͷ����һ���������������ȣ����ζ��ڵأ�ר����־��һ��һ�Ƶ������������ۻ��ޱȡ�\n"NOR,me);
		aer->kill_ob(me);
		me->kill_ob(aer);
		aer->start_busy(999);
		me->start_busy(999);
		
		message_vision(HIC"\n\n$Nһ���ȴ�����ȭ�ӳ������һ�����죬��ͺͷ��������������˫Ŀ�����ؿ���Ѫ��ӿ��\n"
					+"ֻ����ͺͷ��������ǽ��������ĵķ��������������˾�������˫��һ��һ��������ɽ���������˹���\n"NOR,me);
		if (random(ap)>dp/4)
		{
			message_vision(HIY"\n\n$N̤��һ����ȴ������,����һ����������������ת��˫�ƻӳ���һ��һӭ�����Է������������˻�ȥ��\n"
					+"�����ɾ�������һ���ǰ������һ�����������Ʒ�ʯ�������һ���ʯ��������һ���죬ײ��ǽ�ڣ����˳�ȥ��\n"NOR,me);
			aer->set("qi",1);
			aer->set("neili",1);
			if (me->query("neili")>aer->query("neili"))
			{
				me->add("neili",-aer->query("neili"));
			}else me->set("neili",100);
		}else {
			message_vision(HIR"\n\n$N̤��һ����ȴ������,����һ����������������ת��˫�ƻӳ���һ��һӭ�����Է������������˻�ȥ��\n"
						+"���ǰ��������վ��Ǹ���һ������ɾ�������һ�𷴵�������$N�������Ʒ�ʯ�������һ���ʯ��\n"
						+"������һ���죬ײ��ǽ�ڣ����˳�ȥ��\n"NOR,me);						
						me->set("qi",1);
						me->set("neili",0);
						call_out("fight_fail",1,me);
						return 0;
		}
	}else if (arg=="no")
	{
		message_vision(HIC"$N���˻ᣬ�����Լ�ʵ�����ǲ��㣬������ʱ�ȷ�����\n"NOR,me);
		return 0;
		
	}
	me->start_busy(2);
	aer->start_busy(2);
	call_out("check_fight2",2,me,aer);
	return 1;
}

//�������ͷ����״�ս

int check_fight2(object me,object aer)
{
	object zhao;
	zhao=present("zhao min",this_object());

	if (!objectp(me)) 
	{		
		return 1;
	}
	if (!living(me))
	{
		me->delete_temp("mwd");
		call_out("fight_fail",1,me);
		return notify_fail("���վ����ڹ�����������Ϊ��������������ˣ����Բ��ѡ�");
	}
	if (!objectp(aer))
	{
		zhao->greet_ada();
		message_vision(HIR"\n\n\n���������Լ�����ʼ�ˣ��Է���������ؤ�ﳤ�Ϸ����ף����ǽ������֣����Ѿ�׼������Ҫ�μӣ�doujian����\n"NOR,me);
		add_action("do_doujian","doujian");	
		me->set_temp("mwd/step10",1);
		me->delete_temp("mwd/step9");
		me->set_temp("helpwd/fightaer",1);
		me->set("helpwd/fightaer",1);
		return 1;
	}	
	call_out("check_fight2",2,me,aer);
	return 1;

}

int do_doujian()
{
	object ada,me,zhao;
	object weapon;
	me=this_player();
	zhao=present("zhao min",this_object());
	
	ada=present("a da",this_object());
	if (!ada)
	{
		ada=new("d/wudang/taiji/laoda");
		ada->move("d/wudang/zixia");
	}	
	if (!me->query_temp("mwd/step10"))
	{
		return notify_fail("��û��Ī�������������ʲô������");
	}
	message_vision(HIC"\n\n$N�������������콣������ƥ���κα������ϼ��ϣ�Ωһ�Բߣ�ֻ���ɾ����ֶ������С�\n"
						+"Ȼ�����ֵ���ȷ����ı���֮�ԣ�ֻҪ�Է��Ľ������棬�仯���в��⣬�Լ�һ���ֱ���ָ��������ͷ\n"
						+"������һ��������һ������ʱ���ϣ���ζԵУ������ķѳ�������������������$N���Ҵ���̫��ȭ��\n"
						+"�Ѿ��������ˣ�����һ��̫�����������´����㣬������������λʩ�������С�$Nϲ��������лʦ����\n"
						+"$Nתͷ�򰢴��������λǰ�����ҽ��������������̫ʦ��ָ��һ��������������С���\n"NOR,me);

	message_vision(HIW"\n\n�ǰ����$Nԭ�����Լɵ����Լ����б������֣�ռ�˱��ˣ�����ʤ����֪����˵��Ҫ��ѧ���С�\n"
						+"�����ٺò�����������ѧ�Ľ��о��ܾ�����ǲ������衣����֮�������������鶯������Ҳ��\n"
						+"����һ��ʮ�꣬�ٵ�ʱ���ܵ���Ӧ�֣��켫�����������˵�ͷ��˵��������ȥѧ�аգ����������\n"
						+"�㡣ѧ����ʱ����������������������õ��Եĵط�����������̣��޼������ѧ��������������\n"
						+"�������������ð��ʱ����һ��̫���������ܽ��ꡣ\n"NOR,me);

	message_vision(HIG"\n\n������������ϵ���·̫�������ܵð˱���ָ�㼸�У��ٳ�������$N�������彣ô����\n"
						+"�Աߵ�ͯ��ǰ�������������޼ɴ�������ȡ�����Ǳ�ľ�Ƽ����콣��������������Ц����\n"
						+"����ľ�����ϵ��ⲻ���������������������аô����\n"	NOR,me);

	message_vision(HIY"\n\n�����ᵱ��վ�����������ֳֽ����������������˫�ֳɻ�������̧��������ʽһչ�������������¡�\n"
						+"����ǡ����ӳ�ˮ������ɨ������ɨ����һ���е��ݽ�������ʹ����ʮ��ʽ��ָ���롯��˫��ͬʱ��Բ��\n"
						+"���ɵ���ʮ��ʽ���ֽ���ԭ�������޼ɲ�����ʽ��ֻ��ϸ�������С����ڽ��ȡ����಻����֮�⡣\n"	NOR,me);

						
	message_vision(CYN"\n\nֻ���������ʵ������������㿴�����û�У���$N������������ˡ�����������������ǵ���û�У���$N������\n"
						+"����������һС�롣��������������ã���Ҳ��Ϊ���㡣���Լ�ȥ����ա���$N��ͷĬ�롣����һ�ᣬ\n"
						+"�������ʵ��������������ˣ���$N��������������һ��롣��\n"	NOR,me);
	message_vision(HIG"\n\nֻ���������ʵ������������㿴�����û�У���$N������������ˡ�����������������ǵ���û�У���$N������\n"
						+"����������һС�롣��������������ã���Ҳ��Ϊ���㡣���Լ�ȥ����ա���$N��ͷĬ�롣����һ�ᣬ\n"
						+"�������ʵ��������������ˣ���$N��������������һ��롣��\n"	NOR,me);
	
	message_vision(HIY"\n\n$N������������ʦ�Ľ��⣬����̫���������������һ�㡣\n"	NOR,me);
	
	if (!objectp(weapon=me->query_temp("weapon"))
		||me->query_skill_mapped("sword")!="taiji-jian"
		||me->query_skill_mapped("parry")!="taiji-jian")
	{
		return notify_fail(HIR"\n\n�����˸մ��������̫�������㲻����ʹ��,���ȥ�������е����⣿\n"NOR);
	}
	ada->greet_ada();
	ada->kill_ob(me);
	me->kill_ob(ada);
	call_out("last_fight",1,me,ada);
	return 1;
}

int last_fight(object me,object ada)
{
	object lu,he,zhao;
	if (!objectp(zhao=present("zhao min",this_object())))
	{
		zhao=new("d/city/kedian/zhao");
		zhao->move("d/wudang/zixia");
	}	
	if (!objectp(he=present("he biweng",this_object())))
	{
		he=new("d/city/kedian/hebw");
		he->move("d/wudang/zixia");
	}
	if (!objectp(lu=present("lu zhangke",this_object())))
	{
		lu=new("d/city/kedian/luzk");
		lu->move("d/wudang/zixia");
	}
	if (!me)
	{		
		return 1;
	}
	if (!living(me))
	{
		me->delete_temp("mwd");
		call_out("fight_fail",1,me);
		return notify_fail("�㹦���վ���̫������ʹ������Ϊ���������ˣ���ʱ���Բ��ѡ�\n");

	}
	if (!objectp(ada)&& !me->is_fighting())
	{
		message_vision(HIC"\n\n�����ۼ���������ȥ��ȫ����ǣ�˵��������������$N�����ϣ��Ź����䵱�ɡ���\n"
						+"����һ�ӣ��������߰գ��������²������𷽶��ס�ͺͷ������������ʬ�壬�������ߡ�\n"
						+"$N�е����������������º�������࣬���������䵱ɽ����������ϣ�������������ͷץȥ��\n"NOR,me);

		message_vision(HIB"\n\n����������ͷ���г���ͻ������������Ϣ���Ʒ�������һ��������Ⱦ�û������ס���\n"
						+"$Nһ��֮�£�˫�Ʒ��������ֽ����ұ߻�����һ�ƣ����ֽ��˴���߻�����һ�ƣ�����ͬʱ������\n"
						+"ֻ��������ǿ�������о�����һ�������ޱȵĺ����������������ֵ���ڤ���ƣ�\n"NOR,me);
		lu->kill_ob(me);
		me->kill_ob(lu);

		he->kill_ob(me);
		me->kill_ob(he);

		me->delete_temp("mwd/step10");
		me->set_temp("mwd/step11",1);
		me->set_temp("helpwd/fightada",1);
		me->set("helpwd/fightasan",1);
		call_out("check_fight3",10,me,lu,he,zhao);
		return 1;
	}
	call_out("last_fight",2,me,ada);
	return 1;
}

int check_fight3(object me,object lu,object he,object zhao)
{
	object zhang;
	int exp;
	zhang=present("zhang sanfeng",this_object());
	if (!me) return 0;
	
	if (!living(me))
	{
		me->delete_temp("mwd");
		call_out("fight_fail",1,me);
		return notify_fail("�㱻��ڤ���ƺ������£���ʱһ����û�л��������赹�ڵأ����²�ʡ��\n");
	}
	
	if (!me->is_fighting())
	{
		message("channel:chat", HIC"�����졿�ױ��̣�"+me->query("name")+HIC"�ô����ͷ���䵱Ҳ������˶��ѣ�\n"NOR, users());
		message("channel:chat", HIC"�����졿¹�ȿͣ�ʲô̩ɽ������������ڤ������ǰ���������߹�֮�����ٺ٣�\n"NOR, users());
		message("channel:chat", HIC"�����졿��������������"+me->query("name")+HIC"�����ϣ��Ź����䵱�ɣ������ߣ�\n"NOR, users());
		if (objectp(zhao))
			destruct(zhao);
		if (objectp(he)) destruct(he);
		if (objectp(lu)) destruct(lu);
		
		message_vision(HIY"\n\n���˼�$N���ˣ���ʱΧ��������$N΢΢һЦ�������������һ�£���ʾ�������£������������񹦷�����\n"
							+"����ڤ���Ƶ�����֮�����˳�����ͷ����������һ�㲻����˿˿����ð����\n"NOR,me);

		message_vision(HIC"\n\n������ǳ�����Ŀ���$N��΢΢��ͷ��˵����������һս�����������ջ����࣬��\n"
							+"���˺��˺󣬾�ȥ��ɽ������̣��Һúø��㽲����̫���İ��ء���˵��ƮȻ��ȥ��\n"NOR,me);
		if (objectp(zhang))
			destruct(zhang);
		me->set_temp("mwd/over",1);
	    me->set_temp("helpwd/fightxm",1);
		me->set("helpwd/fightxm",1);
		me->set("mwd/over",1);
		me->delete_temp("helpwd");
		me->delete_temp("mwd");
		exp=2000+random(500);
		me->add("combat_exp",exp);
		message_vision(HIY"\n\n�����Ŭ��Ϊ����ɱ�У������˾�������Щ����ֵ������������"HIR+chinese_number(exp)+HIY"�㾭��ֵ��������\n"NOR,me);
		return 1;		
	}
	call_out("check_fight3",2,me,lu,he,zhao);
	return 1;
}

int fight_fail(object me)
{
	object zhao,zhang,lu,he,ada,aer,asan,room;
	room=load_object("d/wudang/houyuan");
	me->set("quest/wd/taiji/time",time());
	me->add("quest/wd/taiji/fail",1);
	if (objectp(zhao=present("zhao min",this_object())))
		destruct(zhao);
	if (objectp(he=present("he biweng",this_object())))
		destruct(he);
	if (objectp(lu=present("lu zhangke",this_object())))
		destruct(lu);
	if (objectp(ada=present("a da",this_object())))
		destruct(ada);
	if (objectp(aer=present("a er",this_object())))
		destruct(aer);
	if (objectp(asan=present("a san",this_object())))
		destruct(asan);
	if (objectp(zhang=present("zhang sanfeng",this_object())))
		if (!objectp(present("zhang sanfeng",environment(room))))
		{
			zhang->move("d/wudang/houyuan");
		}else destruct(zhang);
	me->delete_temp("mwd");
	me->delete_temp("helpwd");

	message_vision(HIR"�ǳ���Ǹ�����ν���䵱Σ��������ʧ�ܣ������书�����˺�������\n"NOR,me);
	return 1;
}
