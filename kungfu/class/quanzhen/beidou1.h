// Code of JHSH
// /d/zhongnan/beidou.h
// �������
// sdong 08/15/98

#include <ansi.h>

//inherit F_DBASE;
inherit F_SSERVER;
string *position = ({
	HIC"��Ȩ"NOR,HIG"����"NOR,HIY"���"NOR,HIM"����"NOR,HIW"���"NOR,HIB"����"NOR,HIR"ҡ��"NOR
});

string *sword = ({
	"������˼�����һ�������ޱȵġ��ֻ�������������ʵ�������д�ȥ��",
	"ʹһ�С���������������������Ʈ�����н�����ʵʵ�ó����㺮��������С�",
	"����һת����Ȼһʽ���ɨҶ����������콣Ӱ��Ю�ž�����ǰɨȥ��",
	"���쳤Ц������ƮȻ�����ڰ��������һ����һʽ�����ʹ��������ػ�����С�",
	"�������Ž���������̤��һ�С������롱����б�̡�",
	"��ǰ��ȥһ�󲽣�ʹ����̽�������������н����һ������Ѹ�����׻�����",
	"����һ������һʱ�������仨�������ó���㽣����ƮȻ�̳���",
	"���н�һָ���������࣬һʱ������Į�����������������",
	"��������Ʈ��ͻȻһת��ͷ�½��ϣ����ս���һ�С���׹��������������Ϣ�ع�����",
	"���һ����һ�С��׺羭�졹��������㻮��һ����Բ�����¡�",
	"��Ȼ���θ߸�Ծ��ʹ�����˼����ġ������н��ó����컨�꣬Ѹ�����������"
});

string *zhen =  ({
	"������󷨹����ƶ����������಻����˲�佫����Χ�����ġ�",
	"����������ƺ��ǰ�������������ӣ������ۻ����ң������ʧ��",
	"ֻ��������󰵺����а���֮�������˲������������ϵ������޷죬����֮������̾Ϊ��ֹ��",
	"�������Խ��ԽС�����ν������˳�һ��������룬��������Ϣ֮�С�"
});

int beidouzhen(object me);
int halt_beidouzhen(object me);
int do_beidouzhen(object ob);
//int beidouzhen(object me);
int halt_beidou(object me);
int stop_beidou();
int beidou_kill(object ob);
void init()
{
		  add_action("stop_beidou", "stop");
		  add_action("do_beidouzhen", "lianzhen");
		   add_action("beidou_kill", "beidou");
		//  add_action("do_beidouzhen2", "start2");
		   //add_action("do_beidou", "beidou"); //��������ɱ��
}
//�����˵�����
int check_ob(object ob,object me)
{
	string ob_name;
	object weapon;
	if( !objectp(ob) )
	{
		return notify_fail("����������ʱ�򣬿�ϧû���ҵ�����ˡ�\n");
	}
	ob_name = ob->query("name");

	if ( !present( ob->query("id"), environment(me) ) )
	{
		return notify_fail("��ϧ"+ob_name+"�������\n");
	}

	if ( ob->query("family/family_name") != "ȫ���" )
	{
		return notify_fail("��ϧ"+ob_name+"����ȫ����ӣ����ᡸ������󡹡�\n");
	}
	if ( ob->query_skill("tiangang-beidouzhen",1) <350)
	{
		return notify_fail("��ϧ"+ob_name+"������󷨲���350�������ᡸ������󡹡�\n");
	}
	if ( ob->query_skill("xiantian-gong",1) <350)
	{
		return notify_fail("��ϧ"+ob_name+"���칦����350�������ᡸ������󡹡�\n");
	}

	if ( ob->query_skill("quanzhen-jianfa",1) <350 ||
	     ob->query("combat_exp",1)<4500000 ||
	     ob->query_skill("dodge",1) <350)
	{
		return notify_fail("��ϧ"+ob_name+"�书̫��ﲻ��350�����޷�������������󡹡�\n");
	}
	return 1;
}
//���ñ�������
void start_beidouzhen(object ob, int mypos,int beidou_time )
{
	//ob�Ƕ���mypos��λ�ô���beidou_time�ǹ�������ֵ
	ob->set_temp("pending/beidou", 1);
	ob->set_temp("beidou_time", beidou_time*2);
	ob->set_temp("bd_pos", mypos);
	ob->set_temp("bd_power",beidou_time);
	ob->start_busy((: beidouzhen :), (:halt_beidou:));
}

//����1
int do_beidouzhen(string arg)
{
	object ob,me = this_player(),weapon;
	int beidou_time,i,mypos=0,power;
	object where;
	string ob_name;
	string name1,name2,name3,name4,name5,name6;
	object ob1,ob2,ob3,ob4,ob5,ob6;

	seteuid(getuid());
	where = environment(me);
/*
	if (!me->query_temp("lianzhen/start"))
	{
		return notify_fail("����δ��������\n");
	}
	*/
	me->delete_temp("qz/yanlian/zhifu");
	me->delete_temp("lianzhen/start");
	if (me->is_busy() || me->query_temp("pending/beidouzhen"))
		return notify_fail("��������æ���ء�\n");

	if( !arg || sscanf(arg, "%s %s %s %s %s %s", name1,name2,name3,name4,name5,name6)!=6 )
		return notify_fail("���������Ҫ��������ɡ���Ҫ��˭�ڡ�������󡹣�\n");

	if( (int)me->query_temp("pending/beidou") )
		return notify_fail("�����ڰڡ�������󡹡�\n");

	ob_name = me->query("name");
	
	if ( me->query("family/family_name") != "ȫ���" )
	{
		return notify_fail("��ϧ�㲻��ȫ����ӣ����ᡸ������󡹡�\n");
	}

	if ( me->query_skill("quanzhen-jianfa",1) <450 ||
	     me->query("combat_exp",1)<4500000 ||
	     me->query_skill("dodge",1) <450)
		return notify_fail("��ϧ���书̫����ᡸ������󡹡�\n");
	//����һ����
	if( !(ob1 = present(name1, environment(me)) ) )
		ob1 = find_player(name1);

	i = check_ob(ob1,me);
	if(  i !=1) return i;
	//���ڶ�����
	if( !(ob2 = present(name2, environment(me)) ) )
		ob2 = find_player(name2);
	i = check_ob(ob2,me);
	if(  i !=1) return i;
//����������
	if( !(ob3 = present(name3, environment(me)) ) )
		ob3 = find_player(name3);
	i = check_ob(ob3,me);
	if(  i !=1) return i;
//�����ĸ���
	if( !(ob4 = present(name4, environment(me)) ) )
		ob4 = find_player(name4);
	i = check_ob(ob4,me);
	if(  i !=1) return i;
//���������
	if( !(ob5 = present(name5, environment(me)) ) )
		ob5 = find_player(name5);
	i = check_ob(ob5,me);
	if(  i !=1) return i;
//����������
	if( !(ob6 = present(name6, environment(me)) ) )
		ob6 = find_player(name6);
	i = check_ob(ob6,me);
	
	if(  i !=1) return i;
//�жϹ�����

	power = me->query_skill("force") + 
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
	power += me->query_skill("sword")+ 
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
	power += me->query("str")+
               ob1->query("str")+
               ob2->query("str")+
               ob3->query("str")+
               ob4->query("str")+
               ob5->query("str")+
               ob6->query("str");
	power += me->query("dex")+
               ob1->query("dex")+
               ob2->query("dex")+
               ob3->query("dex")+
               ob4->query("dex")+
               ob5->query("dex")+
               ob6->query("dex");
	power = power / 140;


	if (power>50) power=50;
	if (power<18) power=18;
/*
	power = me->query_skill("xiantian-gong") + 
               ob1->query_skill("xiantian-gong")+
               ob2->query_skill("xiantian-gong")+
               ob3->query_skill("xiantian-gong")+
               ob4->query_skill("xiantian-gong")+
               ob5->query_skill("xiantian-gong")+
               ob6->query_skill("xiantian-gong");
	power += me->query_skill("sword")+ 
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
	power += me->query_skill("tiangang-beidouzhen")+ 
               ob1->query_skill("tiangang-beidouzhen")+
               ob2->query_skill("tiangang-beidouzhen")+
               ob3->query_skill("tiangang-beidouzhen")+
               ob4->query_skill("tiangang-beidouzhen")+
               ob5->query_skill("tiangang-beidouzhen")+
               ob6->query_skill("tiangang-beidouzhen");
	power = power / 30;*/

//����������ϵ��
	set_temp("ob1",me->query("id"));
	set_temp("ob2",ob1->query("id"));
	set_temp("ob3",ob2->query("id"));
	set_temp("ob4",ob3->query("id"));
	set_temp("ob5",ob4->query("id"));
	set_temp("ob6",ob5->query("id"));
	set_temp("ob7",ob6->query("id"));
	
	message_vision(HIM"$NͻȻ�����ƶ���������ȫ�������ռλ�ã�������ˣ��ұ����ˣ�" 
		+ "�ڵ����ǡ�������󡹵��󷨡�\n"NOR, me);
//ÿһ��id�������������,���ñ��
	start_beidouzhen(me,0,power);
	start_beidouzhen(ob1,1,power);
	start_beidouzhen(ob2,2,power);
	start_beidouzhen(ob3,3,power);
	start_beidouzhen(ob4,4,power);
	start_beidouzhen(ob5,5,power);
	start_beidouzhen(ob6,6,power);
	//me->set_temp("beidou/tianquan",);
	
	return 1;
}
//�ڶ���ģʽ ��,�ָ�ģʽ������߸���ģʽ

int do_beidouzhen2(string arg)
{
	object ob,me,weapon;
	int beidou_time,i,mypos=0,power,bd_power;
	object here;
	string ob_name;
	string name0,name1,name2,name3,name4,name5,name6;
	object ob1,ob2,ob3,ob4,ob5,ob6;

	here = environment( this_player() );

	if( !arg || sscanf(arg, "%s,%s,%s,%s,%s,%s,%s", name0,name1,name2,name3,name4,name5,name6)!=7 )
		return notify_fail("�����������Ҫ��������ɡ���Ҫ��˭�ڡ�������󡹣�\n");

	if( !(me = present(name0, here) ) )
	{
		message_vision( name0+"��ô���ڣ�\n");
		return 0;
	}

	if( !(ob1 = present(name1, environment(me)) ) )
		ob1 = find_player(name1);
	i = check_ob(ob1,me);
	if(  i !=1) return i;

	if( !(ob2 = present(name2, environment(me)) ) )
		ob2 = find_player(name2);
	i = check_ob(ob2,me);
	if(  i !=1) return i;

	if( !(ob3 = present(name3, environment(me)) ) )
		ob3 = find_player(name3);
	i = check_ob(ob3,me);
	if(  i !=1) return i;

	if( !(ob4 = present(name4, environment(me)) ) )
		ob4 = find_player(name4);
	i = check_ob(ob4,me);
	if(  i !=1) return i;

	if( !(ob5 = present(name5, environment(me)) ) )
		ob5 = find_player(name5);
	i = check_ob(ob5,me);
	if(  i !=1) return i;

	if( !(ob6 = present(name6, environment(me)) ) )
		ob6 = find_player(name6);
	i = check_ob(ob6,me);
	if(  i !=1) return i;

	power = me->query_skill("force") + 
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
	power += me->query_skill("sword")+ 
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
	power += me->query("str")+
               ob1->query("str")+
               ob2->query("str")+
               ob3->query("str")+
               ob4->query("str")+
               ob5->query("str")+
               ob6->query("str");
	power += me->query("dex")+
               ob1->query("dex")+
               ob2->query("dex")+
               ob3->query("dex")+
               ob4->query("dex")+
               ob5->query("dex")+
               ob6->query("dex");
	power = power / 140;

	if (power>50) power=50;
	if (power<18) power=18;

	here->set_temp("ob1",me->query("id"));
	here->set_temp("ob2",ob1->query("id"));
	here->set_temp("ob3",ob2->query("id"));
	here->set_temp("ob4",ob3->query("id"));
	here->set_temp("ob5",ob4->query("id"));
	here->set_temp("ob6",ob5->query("id"));
	here->set_temp("ob7",ob6->query("id"));
	
	message_vision(HIM"$NͻȻ�����ƶ���������ȫ�������ռλ�ã�������ˣ��ұ����ˣ�" + "
                      ���ǰڵġ���������󷨡�\n"NOR, me);

	start_beidouzhen(me,0,power);
	start_beidouzhen(ob1,1,power);
	start_beidouzhen(ob2,2,power);
	start_beidouzhen(ob3,3,power);
	start_beidouzhen(ob4,4,power);
	start_beidouzhen(ob5,5,power);
	start_beidouzhen(ob6,6,power);

	return 1;
}
//����ı���ɱ�� by sohu new design
int beidou_kill(object ob)
{
	object me,ob1,ob2,ob3,ob4,ob5,ob6;
	me=this_player();
	//�жϱ���״̬
	
	if (!objectp(ob=present(ob,environment(me))))
	{
		return notify_fail("��Ҫɱ��Ŀ�겻���ֳ���\n");
	}
	//ob=find_player(arg);
	
	if (!ob||environment(ob)!=environment(me)) 
	{
		return notify_fail("��Ҫɱ��Ŀ�겻���ֳ���\n");
	}
	if (me->is_fighting(ob))
	{
		return notify_fail("������������������׷ɱ���ˣ�\n");
	}
	me->kill_ob(ob);
	ob->kill_ob(me);
	if (!objectp(ob1=present(query_temp("ob1"),environment(me)))) 
	{
		
		return notify_fail("�������������ԱĿ�겻���ֳ���\n");
	}
	if (!objectp(ob2=present(query_temp("ob2"),environment(me)))) 
	{
		
		return notify_fail("�������������ԱĿ�겻���ֳ���\n");
	}
	if (!objectp(ob3=present(query_temp("ob3"),environment(me)))) 
	{
		return notify_fail("�������������ԱĿ�겻���ֳ���\n");
	}
	if (!objectp(ob3=present(query_temp("ob3"),environment(me)))) 
	{
		return notify_fail("�������������ԱĿ�겻���ֳ���\n");
	}
	if (!objectp(ob4=present(query_temp("ob4"),environment(me)))) 
	{
		return notify_fail("�������������ԱĿ�겻���ֳ���\n");
	}
	if (!objectp(ob5=present(query_temp("ob5"),environment(me)))) 
	{
		return notify_fail("�������������ԱĿ�겻���ֳ���\n");
	}
	if (!objectp(ob6=present(query_temp("ob6"),environment(me)))) 
	{
		return notify_fail("�������������ԱĿ�겻���ֳ���\n");
	}
	ob1->kill_ob(ob);
	ob2->kill_ob(ob);
	ob3->kill_ob(ob);
	ob4->kill_ob(ob);
	ob5->kill_ob(ob);
	ob6->kill_ob(ob);
	/**/
	return 1;

}

//������������ȥɱ�� 
int do_beidou(string arg)
{
	object ob,weapon,me = this_player();
	int beidou_time,i,mypos=0,power;
	object where;
	string ob_name;
	string name1,name2,name3,name4,name5,name6,name0;
	object ob0,ob1,ob2,ob3,ob4,ob5,ob6;

	seteuid(getuid());
	where = environment(me);

	if (me->is_busy() || me->query_temp("pending/beidouzhen"))
		return notify_fail("��������æ���ء�\n");


	if( !arg || sscanf(arg, "%s %s %s %s %s %s %s", name0,name1,name2,name3,name4,name5,name6)!=7 )
		return notify_fail("���������Ҫ��������ɡ���Ҫ��˭�ڡ��������ɱ˭�� \n" + 
				     "beidou enemy name1 name2 name 3 name4 name 5 name 6\n");

	if( (int)me->query_temp("pending/beidou") )
		return notify_fail("�����ڰڡ�������󡹡�\n");

	ob_name = me->query("name");
	if ( me->query("family/family_name") != "ȫ���" )
		return notify_fail("��ϧ�㲻��ȫ����ӣ����ᡸ������󡹡�\n");

	if ( me->query_skill("quanzhen-jianfa",1) <350 || 
	     me->query("combat_exp",1)<4500000 ||
	     me->query_skill("dodge") <450)
		return notify_fail("��ϧ���书̫�����350�����ᡸ������󡹡�\n");
//��������
	if( !(ob0 = present(name0, environment(me)) ) )
		return notify_fail("��ϧ��Ҫɱ���˲������\n");

	if( !(ob1 = present(name1, environment(me)) ) )
		ob1 = find_player(name1);
	i = check_ob(ob1,me);
	if(  i !=1) return i;

	if( !(ob2 = present(name2, environment(me)) ) )
		ob2 = find_player(name2);
	i = check_ob(ob2,me);
	if(  i !=1) return i;

	if( !(ob3 = present(name3, environment(me)) ) )
		ob3 = find_player(name3);
	i = check_ob(ob3,me);
	if(  i !=1) return i;

	if( !(ob4 = present(name4, environment(me)) ) )
		ob4 = find_player(name4);
	i = check_ob(ob4,me);
	if(  i !=1) return i;

	if( !(ob5 = present(name5, environment(me)) ) )
		ob5 = find_player(name5);
	i = check_ob(ob5,me);
	if(  i !=1) return i;

	if( !(ob6 = present(name6, environment(me)) ) )
		ob6 = find_player(name6);
	i = check_ob(ob6,me);
	if(  i !=1) return i;

	power = me->query_skill("force") + 
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
	power += me->query_skill("sword")+ 
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
	power += me->query("str")+
               ob1->query("str")+
               ob2->query("str")+
               ob3->query("str")+
               ob4->query("str")+
               ob5->query("str")+
               ob6->query("str");
	power += me->query("dex")+
               ob1->query("dex")+
               ob2->query("dex")+
               ob3->query("dex")+
               ob4->query("dex")+
               ob5->query("dex")+
               ob6->query("dex");
	power = power / 140;

	if (power>50) power=50;
	if (power<18) power=18;

	set_temp("ob1",me->query("id"));
	set_temp("ob2",ob1->query("id"));
	set_temp("ob3",ob2->query("id"));
	set_temp("ob4",ob3->query("id"));
	set_temp("ob5",ob4->query("id"));
	set_temp("ob6",ob5->query("id"));
	set_temp("ob7",ob6->query("id"));
	
	start_beidouzhen(me,0,power);
	start_beidouzhen(ob1,1,power);
	start_beidouzhen(ob2,2,power);
	start_beidouzhen(ob3,3,power);
	start_beidouzhen(ob4,4,power);
	start_beidouzhen(ob5,5,power);
	start_beidouzhen(ob6,6,power);

	me->kill_ob(ob0);
	ob1->kill_ob(ob0);
	ob2->kill_ob(ob0);
	ob3->kill_ob(ob0);
	ob4->kill_ob(ob0);
	ob5->kill_ob(ob0);
	ob6->kill_ob(ob0);

	ob0->kill_ob(me);
	ob0->kill_ob(ob1);
	ob0->kill_ob(ob2);
	ob0->kill_ob(ob3);
	ob0->kill_ob(ob4);
	ob0->kill_ob(ob5);
	ob0->kill_ob(ob6);

	return 1;
}
//������ʧ
void destruct_me(object me)
{
	destruct(me);
}
//��������뿪��״��
void check_leaving(object me)
{
	string name = me->query("id");

	if( name == "qi zhicheng" ||
	    name == "shen zhifan" ||
	    name == "fang zhiqi" ||
	    name == "chen zhiyi" ||
	    name == "cui zhifang" )
	{
		object enemy = offensive_target(me);
		if( !objectp(enemy) && !me->is_busy() && !me->is_fighting() )
		{
			message_vision(HIY"\n$N���˸�鮵���ƶ���ȸ����ˣ�˵��Ϳ첽�뿪�ˡ�\n"NOR, me);
			call_out("destruct_me",10,me);
			return;
		}

		call_out("check_leaving",5,me);
	}
}
//main ������
int beidouzhen(object me)
{
	object  where = environment(this_player());
	int beidou_time = (int)me->query_temp("beidou_time");
	object room, obj,enemy,weapon;
	int cost, bonus,mypos=me->query_temp("bd_pos");
	int power;
	object ob1,ob2,ob3,ob4,ob5,ob6,ob7;

//���ǲ���
	if( !(room = environment(this_player())) )
	{
		if(!objectp(weapon = me->query_temp("weapon"))
		||me->query_skill("sword")!="quanzhen-jianfa"
		||me->query_skill("parry")!="quanzhen-jianfa"
		|| (string)weapon->query("skill_type") != "sword" )
		{
			message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ����" + 
					"�˳���������󡹡�\n"NOR, me);
		}
		else
			message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ����" + 
					"�˳���������󡹡�\n"NOR, me);
		
		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) �� %d ���� Lianzhen �õ� %d ����� %d Ǳ�ܡ�\n", 
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		//tell_object(me,"�������Ǵ�������"+me->name(),+"�õ�"+me->query_temp("qz/jobexp")+);
		message_vision(HIY"$N���δ�������������ʱ"+chinese_number(time()-me->query_temp("qz/jobtime"))+"�룬�����"+chinese_number(me->query_temp("qz/jobexp"))+"�����"+chinese_number(me->query_temp("qz/jobpot"))+"��Ǳ�ܣ�\n"NOR,me);
		me->remove_all_enemy();
		me->delete_temp("pending/beidou");
		me->delete_temp("beidou_time");
		me->delete_temp("bd_pos");
		me->delete_temp("bd_power");
		//����뿪״��
		call_out("check_leaving",2,me);
		return 0;
	}

	enemy = offensive_target(me);
//��������ʱ�䵽��
	if ( beidou_time < 1 && 
	     !me->query_enemy()&& 
	     !objectp(enemy) && 
	     !me->is_busy() && 
	     !me->is_fighting() )
	{
		if(!objectp(weapon = me->query_temp("weapon")) 
		 ||me->query_skill("sword")!="quanzhen-jianfa"
		 ||me->query_skill("parry")!="quanzhen-jianfa"
		 || (string)weapon->query("skill_type") != "sword" )
		{
			message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ����" + 
                                    "�˳���������󡹡�\n"NOR, me);
		}
		else
			message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ����" + 
                                   "�˳���������󡹡�\n"NOR, me);

		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) �� %d ���� Lianzhen �õ� %d ����� %d Ǳ�ܡ�\n",
					ctime(time()),
					me->name(),
					getuid(me),
					time()- me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		message_vision(HIY"$N���δ�������������ʱ"+chinese_number(time()-me->query_temp("qz/jobtime"))+"�룬�����"+chinese_number(me->query_temp("qz/jobexp"))+"�����"+chinese_number(me->query_temp("qz/jobpot"))+"��Ǳ�ܣ�\n"NOR,me);

		me->remove_all_enemy();
		me->delete_temp("pending/beidou");
		me->delete_temp("beidou_time");
		me->delete_temp("bd_pos");
		me->delete_temp("bd_power");
		call_out("check_leaving",10,me);

		return 0;
	}
//������������������
	if ( me->query("neili") < 60 || me->query("jingli")<50 )
	{
		if(!objectp(weapon = me->query_temp("weapon")) || 
		   (string)weapon->query("skill_type") != "sword" )
		{
			message_vision(HIY"\n$N������֧��ֻ���������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ��" + 
					 "����������һ�����˳���������󡹡�\n"NOR, me);
		}
		else
			message_vision(HIY"\n$N������֧��ֻ���������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������" + 
					 "������һ�����˳���������󡹡�\n"NOR, me);

		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) �� %d ���� Lianzhen �õ� %d ����� %d Ǳ�ܡ�\n",
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		message_vision(HIY"$N���δ�������������ʱ"+chinese_number(time()-me->query_temp("qz/jobtime"))+"�룬�����"+chinese_number(me->query_temp("qz/jobexp"))+"�����"+chinese_number(me->query_temp("qz/jobpot"))+"��Ǳ�ܣ�\n"NOR,me);

		me->remove_all_enemy();
		me->delete_temp("pending/beidou");
		me->delete_temp("beidou_time");
		me->delete_temp("bd_pos");
		me->delete_temp("bd_power");
		call_out("check_leaving",2,me);
	
		return 0;
	}
//������鱻����
	if( !(room->query_temp("ob1",1) &&
		objectp(ob1=present( room->query_temp("ob1",1),where) )  && 
		ob1->query_temp("beidou_time") &&
		objectp(ob2=present( room->query_temp("ob2",1),where) )  && 
		ob2->query_temp("beidou_time") &&
		objectp(ob3=present( room->query_temp("ob3",1),where) )  && 
		ob3->query_temp("beidou_time") &&
		objectp(ob4=present( room->query_temp("ob4",1),where) )  && 
		ob4->query_temp("beidou_time") &&
		objectp(ob5=present( room->query_temp("ob5",1),where) )  && 
		ob5->query_temp("beidou_time") &&
		objectp(ob6=present( room->query_temp("ob6",1),where) )  && 
		ob6->query_temp("beidou_time") &&
		objectp(ob7=present( room->query_temp("ob7",1),where) )  && 
		ob7->query_temp("beidou_time") ))
	{
		if(!objectp(weapon = me->query_temp("weapon")) || 
		   (string)weapon->query("skill_type") != "sword" )
		{
			message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ����" + 
					"�˳���������󡹡�\n"NOR, me);
		}
		else
			message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ����" + 
					"�˳���������󡹡�\n"NOR, me);
		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) �� %d ���� Lianzhen �õ� %d ����� %d Ǳ�ܡ�\n", 
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		message_vision(HIY"$N���δ�������������ʱ"+chinese_number(time()-me->query_temp("qz/jobtime"))+"�룬�����"+chinese_number(me->query_temp("qz/jobexp"))+"�����"+chinese_number(me->query_temp("qz/jobpot"))+"��Ǳ�ܣ�\n"NOR,me);

		me->remove_all_enemy();
		me->delete_temp("pending/beidou");
		me->delete_temp("beidou_time");
		me->delete_temp("bd_pos");
		me->delete_temp("bd_power");
		room->delete_temp("ob1");
		room->delete_temp("ob2");
		room->delete_temp("ob3");
		room->delete_temp("ob4");
		room->delete_temp("ob5");
		room->delete_temp("ob6");
		room->delete_temp("ob7");
		call_out("check_leaving",2,me);

		return 0;
	}


	beidou_time = beidou_time-1;
	me->set_temp("beidou_time", beidou_time);
	bonus = random( ( me->query("int")+me->query("con")+25 ) / 30 ) + 
		 (me->query("int")+me->query("con")+25 ) / 30;
	if( bonus > 4 ) bonus = 4;

	//if( (int)me->query("potential") < me->query_potential_limit() )
	
	me->add("potential", random(bonus));
	me->add( "combat_exp", random(bonus));
//���Ӵ�������
	if (me->query_skill("tiangang-beidouzhen",1) < me->query_skill("xiantian-gong",1))
	{
		me->improve_skill("tiangang-beidouzhen", me->query_int() + random(me->query("int") + me->query_skill("tiangang-beidouzhen",1) / 8));
	}
	me->add_temp("qz/jobpot", bonus);
    me->add_temp("qz/jobexp", bonus*3/2);

	enemy = offensive_target(me);

	power = me->query_temp("bd_power",1)*4;

	me->add_temp("apply/parry",power);
	me->add_temp("apply/armor",power);
//���������æµ������
	if( random(3)==1 )
	{
		tell_room(environment(me), HIR"\n" + zhen[(int)random(4)] +"\n"NOR, this_object());

		if( objectp(enemy) && objectp( present( enemy->query("id"),environment(me) )) )
			enemy->add_busy( 1+random(2) );
		if (!random(4))
			enemy->add_condition("no_exert",1);
	}

	if( objectp(enemy) && objectp( present( enemy->query("id"),environment(me) )) )
	{
		//if( random(5)==1 )
		//{
			if(random(2)==0)
				message_vision("\n" + position[mypos] + "λ�ϵ�$N������������񹦣�" + 
						"��Ȼ����������������ǰһ��, ����", me);
			else message_vision("\n" + position[mypos] + "λ�ϵ�$Nͦ��������������" + 
						"����ƮƮ��������硣ֻ��", me);
			
			me->add_temp("apply/damage",power/2);
			me->add_temp("apply/attack",power/2);
			COMBAT_D->do_attack(me, enemy, me->query_temp("weapon"),3);
			me->add_temp("apply/damage",-power/2);
			me->add_temp("apply/attack",-power/2);
			me->add("jingli", -15-random(15));
			me->add("neili", -20-random(20));
		//}
	}
	else
	{
		if ( random(6)==1 )
		{
			if( ( weapon = me->query_temp("weapon") )
				&& (string)weapon->query("skill_type") == "sword" )
			{
				message_vision("\n" + position[mypos] + "λ�ϵ�$N"+ sword[random(10)]+"\n", me);
			}

			me->add("jingli", -15-random(10));
			me->add("neili", -20-random(15) );
		}
	}

	me->add_temp("apply/parry",-power);
	me->add_temp("apply/armor",-power);

	if (beidou_time > -1)
		return 1;

	me->delete_temp("pending/beidou");
	me->delete_temp("beidou_time");
	me->delete_temp("bd_pos", mypos);
//������
	if(!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword" )
	{
		message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ����" + 
				"�˳���������󡹡�\n"NOR, me);

		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) �� %d ���� Lianzhen �õ� %d ����� %d Ǳ�ܡ�\n", 
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file. 
		message_vision(HIY"$N���δ�������������ʱ"+chinese_number(time()-me->query_temp("qz/jobtime"))+"�룬�����"+chinese_number(me->query_temp("qz/jobexp"))+"�����"+chinese_number(me->query_temp("qz/jobpot"))+"��Ǳ�ܣ�\n"NOR,me);

	}
	else
	{
		message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ����" + 
				"�˳���������󡹡�\n"NOR, me);
		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) �� %d ���� Lianzhen �õ� %d ����� %d Ǳ�ܡ�\n",
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		message_vision(HIY"$N���δ�������������ʱ"+chinese_number(time()-me->query_temp("qz/jobtime"))+"�룬�����"+chinese_number(me->query_temp("qz/jobexp"))+"�����"+chinese_number(me->query_temp("qz/jobpot"))+"��Ǳ�ܣ�\n"NOR,me);

	}
	call_out("check_leaving",5,me);
	return 0;
}
//����������
void restart (object me)
{
	start_beidouzhen(me, me->query_temp("bd_pos"), me->query_temp("beidou_time",1) );
}
//��ͣ������,��restart��Ӧ
int halt_beidou(object me)
{
	object weapon;
	int beidou_time = (int)me->query_temp("beidou_time",1);
	if (beidou_time > 0)
	{
		if( !living(me) ) return 1;

		if(random(2)==1)
		{
			message_vision(HIG"\n$N������һ�������ˤ��������\n"NOR, me);
		}
		else message_vision(HIG"\n$N����Ļ��˼��Σ�������վ���˲��ӡ�\n"NOR, me);
		call_out("restart",4,me);
		return 1;
	}

	if(!objectp(weapon = me->query_temp("weapon"))
	   || (string)weapon->query("skill_type") != "sword" )
	{
		message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ����" + 
				"�˳���������󡹡�\n"NOR, me);
	}
	else
		message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ����" + 
				"�˳���������󡹡�\n"NOR, me);
	me->delete_temp("pending/beidou");
	me->delete_temp("beidou_time");
	me->delete_temp("bd_pos");
	me->delete_temp("bd_power");
	return 1;
}
//ֹͣ����
int stop_beidou()
{
	object weapon,me=this_player();
	if(!me->query_temp("pending/beidou"))
		return notify_fail("ͣʲô���㲻�����С�������󡹡�\n");
	if(!objectp(weapon = me->query_temp("weapon"))
	   || (string)weapon->query("skill_type") != "sword" )
	{
		message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ����" + 
				"�˳���������󡹡�\n"NOR, me);
	}
	else
		message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ����" + 
				"�˳���������󡹡�\n"NOR, me);
	me->remove_all_enemy();
	me->delete_temp("pending/beidou");
	me->delete_temp("beidou_time");
	me->delete_temp("bd_pos");
	me->delete_temp("bd_power");
	return 1;
}
