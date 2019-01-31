// /area/jiangbei/wudang/zixia.c ������
// By River@SJ

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIM"������"NOR);
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

       // set("outdoors", "�䵱");

        setup();
}
/*
void init()
{
	object me=this_player();
	if (me->query_temp("mwd/step6"))
	{
		me->start_busy(3);
		call_out("do_find",2+random(3),me);
	}

}
int do_find(object me)
{
		object kongxiang;
		message_vision(HIG"\n\n$N���н��ǣ��첽��ɣ��������ܵ�С��ʿ���ƺ����ڸ���æµ���ƺ��������ѻ�û�з��������в��ɴ󶨡�\n\n"
							+"����$N���߼䣬��Ȼ����ǰ��һλ����ɮ�����ڴҴұ��ߣ���ɫ�ƺ����ǻ��š�\n"NOR,me);
	    me->delete_temp("mwd/step6");
		
		kongxiang=new("d/wudang/taiji/kongxiang");
		kongxiang->move(this_object());
		kongxiang->greeting();
		
		me->set_temp("mwd/step7",1);
		call_out("find_yudaiyan",3,me,kongxiang);
		return 1;
}
int find_yudaiyan(object me,object kongxiang)
{
	message_vision(HIC"\n\n$N�����ɻ�������һ·��������������������ͨ�������˵���Ա����������࿴�����������ǻ��ŵ����ӡ�\n\n"
							+"����ã��������С��ͯ�Ĳ���£������������Ϳ���̸�˻ᣬ��ɫ���ǽ��ţ��Ը�С��ͯ����̧��ȥ����ʦү��\n"NOR,me);
	call_out("zhang_come",3,me,kongxiang);	
	return 1;
}
int zhang_come(object me,object kongxiang)
{

	object zsf;
	object room;
		room=load_object("d/wudang/houyuan");
	message_vision(HIC"\n\n��յ��⾰��һλ��ü�԰׵��ϵ��˻��������������������ֵĿ�ɽ��ʦ�����ᣡ��\n\n"NOR,me);
	if (objectp(zsf=present("zhang sanfeng",room)))
	{
		zsf->move(this_object());
	}else {

		zsf=new("kungfu/class/wudang/zhang");
		zsf->move(this_object());
		//zsf->command("chat ....");

	}

	call_out("kx_kill",2,me,kongxiang,zsf);

}

int kx_kill(object me,object kongxiang,object zsf)
{
	
	message_vision(HIC"\n\n����һ����������������ͨһ���򵹣�������ޡ�\n\n"NOR,me);
	kongxiang->greet2();
	message_vision(HIY"\n\n�������ۼ���������ѹ���Ҳ����̾��һ���������������������������������顣��˵�վ��뽫������������\n"NOR,me);
	message_vision(HIY"\n\n��֪��ʱ������ͻ�䣬�����Ȼ�����Ŀ������һ�������������С��������\n"NOR,me);
	kongxiang->kill_ob(zsf);
	zsf->kill_ob(kongxiang);
	zsf->receive_wound("qi",2000+random(1000),kongxiang);
	zsf->apply_condition("neishang",10);
	me->delete_temp("mwd/step7");
	me->set_temp("mwd/step8",1);
	add_action("do_heal","heal");
	return 1;
}*/
/*
int do_heal(string arg)
{
	object me=this_player();
	object zsf;
	zsf=present("zhang sanfeng",this_object());
	if (!zsf) return 0;
	if (!arg||arg!="zhang sanfeng")
	{
		return notify_fail("��ҪΪ˭���ˣ�");
	}
	message_vision(HIC"\n\n$N������𣬽��ִ���$n�ı����˹�Ϊ$n���ˡ�\n"NOR,me,zsf);
	message_vision(HIY"\n\n\n��$N��ȫ����ת֮�£�$n���ƴ�Ϊ��ת�����漴������һ����Ѫ��$n��֪������һ����ʵ���˲��ᡣ\n"NOR,me,zsf);
	message_vision(HIR"\n\n$ņͷ����һ��$N����Ц����û�뵽���䵱�ɾ�Ȼ������˸��֣�����˭�����£�\n"NOR,me,zsf);
	message_vision(HIG"\n\n$n˵��������һ���������˵ã��������䵱Ҫ�����ˣ�������������\n"NOR,me,zsf);
	
	message_vision(HIC"\n\n�����ĬȻ������֪ɽ�ϳ���ʦ�����Լ�֮�⣬�������Ĵ����ӵ��书����������������У�\n"
						+"ֻ��ͽȻ����������֮�£�Ω���Լ���ȴһ�����͵��˷�����������ʦ���ܵ����ˣ��պ��ٸ����\n"
						+"�����������������飬��ȥ����Щ��˵���ұ������������������������š��������Ӧ��ȥ�ˡ�"NOR,me);
����
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
						+"һ�������Ƴ������������������ϵ���Ȼ��ͷ���������ǰ���ͽ��ͽ���������ˡ�����һ���ֺ��������������ð���\n"
						+"��һ�ѻ������������˵��������һ����������������������ϵ������Ǳ���������������ס������\n"
						+"�󵽸�������������ʾ�ڣ��ô����������ѧ̩���϶�������ģ������\n"NOR,me);
	
	call_out("zhao_come",2+random(3),me,zsf);
	return 1;
}*/
/*
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

}*/
//��һ��ս����շ�ħ��ͨ���������ָ��̫��ȭ
/*
int do_bishi1()
{
	object me=this_player();
	object asan;
	asan=present("a san",this_object());
	if (!asan)
	{
		asan=new("d/wudang/taiji/asan");
		asan->move(this_object());
	}
	message_vision(HIY"$N����Ҫ��$n��ǰ��ʾ�䵱�ɵ����磬�˹�����˵��������ʦЪϢƬ�̣����Сë����ͽ�����������ˡ�\n"
						+"Ҳ��������ʶ��ʶ���䵱�ɵ��书��ʡ�����������죬��֪��ԭ���ܡ�\n"NOR,me,asan);
    message_vision(HIY"��������������֪�����ڹ��˵ã�����΢΢Ц��������Ҳ�ã���Ȼ��λ��շ�ħ�񹦵�Ӣ�����ʶ��ʶ��\n"
						+"���䵱���񼼣��ǾͰ������½������̫��ȭ�İ���˵���������������Ƿ����ڻ��ͨ��\n"NOR,me,asan);
	asan->kill_ob(me);
	me->kill_ob(asan);

//	check_fight1(me,asan);

}

*/

//�ڶ���ս�����ڹ���ƴ��̫����

//������ս��������