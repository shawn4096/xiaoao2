// dong1.c
// sohu
#include <ansi.h>
inherit ROOM;
#include "/d/suzhou/npc/lchj.h"
int check_fight(object me,object laozu,object shui);

void create()
{
        set("short",YEL"Ұɽ��"NOR);
        set("long",@LONG
����һ��СС��ɽ�����������˲���֮�ء���춴˵رȽ�����
���Ǵ�ѩɽ�����Ȼ��Ѩ�����˺���Ѱ����������
LONG );
        set("exits",([
                "out" : "/d/xueshan/xuegu2",
        ]));
		set("task",1);
        set("objects", ([
               "/d/xuedao/obj/dachang" :1, 
        ]));
        setup();
  		replace_program(ROOM);
}

int init()
{
	object shui;
	object me=this_player();
	
	if (me->query_temp(QUESTDIR3+"shuitellstory")&&this_object()->query("task")>0)
	{
		message_vision(HIC"$N�������ɽ������ˮ�ϻ�û��������������ܴ���!\n"NOR,me);
		message_vision(HIM"�����������˺�������ʦ�ã���ԭ�����������ʦ�����ҵ���ÿడ����\n"NOR,me);

		call_out("wang_come",2+random(3),me);
		//���ü�����
		//call_out("check_fight",1,me);

		me->set_temp(QUESTDIR3+"fightwang",1);
		me->delete_temp(QUESTDIR3+"shuitellstory");
		this_object()->add("task",-1);

	}
		        //���ñ���ˮ�Ϻ���
	//add_action("do_baohu", "baohu");
	add_action("do_qiang", "qiang");
	add_action("do_canwu", "canwu");

}

int wang_come(object me)
{
		object wang;
		if (!me) return 0;
	
		if (me->query("gender")=="����")
			message_vision(HIW"��Х����������ӣ�һ��$Nվ�Աߣ���ʱ��ŭ���ȵ�������ʦ�����������ԭ��������С�����ڴ˹�����ʦ�ã���\n"NOR,me);
		if (me->query("gender")=="Ů��")
			message_vision(HIW"��Х��һ��$Nվ��ˮ���Աߣ���ʱ��ŭ���ȵ�����ԭ��������Сɧ���ڴ��ջ������ʦ�ø������ԣ���\n"NOR,me);

		if (!objectp(wang=present("wang xiaofeng",this_object())))
		{
			wang=new("d/xuedao/npc/wangxiaofeng");
			wang->move("d/xuedao/dong");
		}
		wang->kill_ob(me);
		me->kill_ob(wang);
		me->set_temp(QUESTDIR3+"killwang",1);

		message_vision(HIR"��Х������ȵ�����ʦ��������ʦ��������������������۸���ʦ�ã���\n"NOR,me);
		if (living(me))
			call_out("lhls_come",10+random(10),me);
		return 1;
}
//�仨��ˮ����

int lhls_come(object me)
{
		object lu,hua,liu,shui;
		if (!me) return 0;

		tell_object(me,HIY"��~~~~~~~~~~~~~~~~~~~~~~~��\n"NOR);
		tell_object(me,HIG"~~~~~~~~��~~~~~~~~~~~~~~~��\n"NOR);
		tell_object(me,HIW"~~~~~~~~~~~~~~~~��~~~~~~~��\n"NOR);
		tell_object(me,HIM"~~~~~~~~~~~~~~~~~~~~~~~ˮ��\n"NOR);

		message_vision(HIR"�仨��ˮ�������Ĵ�����һ��$Nվ��ˮ���Աߣ���ʱ��ŭ���ȵ�����ԭ��������Ū��ı����������\n"NOR,me);

		if (!objectp(lu=present("lu tianshu",this_object())))
		{
			lu=new("d/xuedao/npc/lutianshu");
			lu->do_copy(me);
			lu->move("d/xuedao/dong");

		}
		if (!objectp(hua=present("hua tiegan",this_object())))
		{
			hua=new("d/xuedao/npc/huatiegan");
			hua->do_copy(me);
			hua->move("d/xuedao/dong");

		}
		if (!objectp(liu=present("liu chengfeng",this_object())))
		{
			liu=new("d/xuedao/npc/liuchengfeng");
			liu->do_copy(me);
			liu->move("d/xuedao/dong");

		}
		if (!objectp(shui=present("shui dai",this_object())))
		{
			shui=new("d/xuedao/npc/shuidai");
			shui->do_copy(me);
			shui->move("d/xuedao/dong");

		}

		lu->kill_ob(me);			message_vision(HIG"½����ȵ����������ؼ������㲻������\n"NOR,me);

		me->kill_ob(lu);
		hua->kill_ob(me);			message_vision(HIG"�����ɺȵ����������ؼ������㲻������\n"NOR,me);

		me->kill_ob(hua);
		liu->kill_ob(me);			message_vision(HIG"���з�ȵ����������ؼ������㲻������\n"NOR,me);

		me->kill_ob(liu);
		shui->kill_ob(me);			message_vision(HIG"ˮ᷺ȵ����������ؼ������㲻������\n"NOR,me);

		me->kill_ob(shui);
		
		me->set_temp(QUESTDIR3+"fightlhls",1);

		if (living(me))
			call_out("shuisheng_come",10+random(10),me);
		return 1;
}
//ˮ������

void shuisheng_come(object me)
{
        object shui;
		if (!me) return;


		if (!objectp(shui=present("shui sheng",environment(me))))
		{
		    shui=new("d/xuedao/npc/shuisheng");
			shui->move("d/xuedao/dong");
			
		}
		me->set_temp(QUESTDIR3+"shuicomedong",1);

		message_vision(HIC"\nˮ�ϻŻ����ŵ����˽�������ɫ�԰ף�����������\nһ���ܣ�һ�߲�ס��󿴣��ƺ�������������׷���Ƶá�\n"NOR, me);
		if (living(me))
			call_out("laozu_come",3,me,shui);
		return;
}
//����

int laozu_come(object me,object shui)
{
		object laozu;
		if (!me) return 0;

		if (!objectp(laozu=present("xuedao laozu",environment(me))))
        {
			  laozu=new("/d/xuedao/npc/laozu.c");
		      laozu->move(environment(me));
		      message_vision(HIY"\n���⴫��һ����Ц��һ��ɫ���е��Ϻ��п����������У������������\n"NOR,me);
			
        }
		message_vision(HIY"\nѪ������ɫ���Եض�ˮ��Ц��������ү���׽�˸���ƷС椡�˵����Ц�����ؾͳ�ˮ��ץȥ��\n"NOR,me);

		laozu->hit_ob(shui);
		shui->kill_ob(laozu);
		me->set_temp(QUESTDIR3+"laozukillshui",1);
		//���ü�⺯��
	//	call_out("check_fight",10,me,shui);
		//��������
		if (living(me)&&objectp(laozu))
			call_out("diyun_come",3+random(2),me,laozu);
		return;
}
//��ʼ��ս����vsѪ������
int diyun_come(object me,object laozu)
{
	object diyun;
	if (!me) return 0;
	message_vision(HIR"��ʱ�����⴫�����һ��������ס�֣���\n"NOR,me);
	message_vision(HIG"һ����������ũ���������ӽ��붴�к�Ѫ�����涷�����������ǵ������ˣ�\n"NOR,me);

	if (!objectp(diyun=present("di yun",environment(me))))
	{
		diyun=new("d/xueshan/npc/diyun");
		diyun->move(environment(me));
	}
	//laozu->kill_ob();
	if (me->query("combat_exp")<17000000)
		laozu->set("combat_exp",17000000);
	else laozu->set("combat_exp",me->query("combat_exp")*5/4);
	
	laozu->set("jiali",1);
	diyun->set("jiali",1);
	laozu->add_temp("apply/parry",200);
	laozu->add_temp("apply/armor",100);
	laozu->add_temp("apply/defense",200);

	laozu->hit_ob(diyun);
	diyun->hit_ob(laozu);
	
	message_vision(CYN"Ѫ������͵��ƶ�����˵����ʼ��������\n"NOR,me);
	message_vision(YEL"���е��⽣Ӱ�������ݺᣬ�㿴ˮ�ϴ���һ�ԣ��ƺ����ǽ��š�\n������ˮ��˵������ˮ��������ڲ��ú��£����������㡱��\n"NOR,me);
	add_action("do_baohu", "baohu");

	return 1;
}

//����ˮ��
int do_baohu(string arg)
{
	object me,shui,laozu,diyun;
	me=this_player();
	
	shui=present("shui sheng",environment(me));
	laozu=present("xuedao laozu",environment(me));
	diyun=present("di yun",environment(me));
	if (!me->query_temp(QUESTDIR3+"laozukillshui")) return notify_fail("����Ե�޹��ſ�˫��Ҫ������ô��\n");
	if (time()-me->query(QUESTDIR+"time")<86400)
	{
		return notify_fail("���Ѿ�������һ�Σ�����������\n");
	}


	if (!arg||arg!="ˮ��") return notify_fail("��Ҫ����˭��\n");

	if (!shui) return notify_fail("�㶯��̫����ˮ���Ѿ����ڴ˵أ��㷢�����˰ɣ�\n");
	if (!laozu) return notify_fail("�����Ѿ���ɱ�ˣ����豣��ˮ�ϣ�\n");
	if (!diyun) return notify_fail("���Ʋ�С�ı�ɱ�ˣ�ˮ�����뼫�ȱ���֮�У�ʧ�ܣ�\n");
	
	if (me->query_temp(QUESTDIR3+"baohu"))
	{
		return notify_fail("������ʵʩ���������У�\n");
	}

	message_vision(HIG"$N�ۼ�ˮ��Σ������$n˵������ˮ���ﲻҪ�ż������������㣡��\n"NOR,me,shui);
	message_vision(HIY"$n���һ��������$N�ֿ�ʼװ������ˣ����Ӹɵľ���װ�Ƶ�Ӣ�ۣ���\n"NOR,me,laozu);
	
	message_vision(HIM"$nѪ�����������·���˸����Ƶã���������һƬ�������ֵ�Ѫ��\n"NOR,me,laozu);

	if (me->query("combat_exp")<17000000)
		laozu->set("combat_exp",17000000);
	else laozu->set("combat_exp",me->query("combat_exp")*5/4);
	//laozu->set("jiali",250);
	if (me)
		laozu->kill_ob(me);
	if (diyun)
		laozu->kill_ob(diyun);
	
	laozu->kill_ob(shui);
	me->set_temp(QUESTDIR3+"baohu",1);
//�Ǻ���ͦס10��
//	if (living(me)&&objectp(laozu)&&objectp(shui))
		call_out("check_fight",10,me,laozu,shui);
	return 1;
}
//�������
int do_fail(object me)
{
	
	me->set(QUESTDIR+"time",time());
	me->add(QUESTDIR3+"fail",1);
	me->set(QUESTDIR+"combat",me->query("combat_exp"));
	me->delete_temp(QUESTDIR3);

	message_vision(HIC"\n\n\n$N�Ȼ�ˮ��ʧ��,���ٽ�����!\n\n\n"NOR,me);

}
int check_fight(object me,object laozu,object shui)
{
	object weapon;
	if (!me) return 1;
	
	if (!shui) 
	{
		tell_object(me,HIR"����Ϊ�Ȼ�ˮ�ϲ���������ˮ��Ϊ���������ӣ�����ʧ�ܣ�\n"NOR);

		do_fail(me);
		return 1;
	}
	if (environment(me)!=this_object())
	{
		tell_object(me,HIR"����Ϊ�����뿪ɽ�����Ȼ�ˮ�ϲ�������������ʧ�ܣ�\n"NOR);
		do_fail(me);
		return 1;
	}
	//laozu=present("xuedao laozu",environment(me));
	
	if (!objectp(laozu))
	{
		tell_object(me,HIR"���治�ڴ˵أ���������޷���������������ʧ�ܣ�\n"NOR);
		do_fail(me);
		return 1;
	}

	weapon=laozu->query_temp("weapon");
	message_vision(HIW"$N�е���������ɱ���ˣ���˵���˽���ȥ��������֦����$n���ϡ�\n"NOR, shui, laozu);
	if (weapon)
	{
		message_vision(HIC"����ƽʱ��$n���ܸ�$N���У�����ʱ˥��֮�࣬��������ԭ���İ�ɣ���ָһ�ɣ�"+weapon->query("name")+HIC"������ء�\n"NOR,shui, laozu);
		weapon->move(environment(me));
	}
	message_vision(HIC"\n\n����Ѫ�������ֳ�Ѫ�����׶���׺�����������£�$N��Ȼ��ʶ�������뽫���ϵ���ѵ���������\n\n"NOR,me);
	message_vision(HIY"\n����һ������Ѫ�����������ǰѵ����ڳ����е��˿��¶����Ի�����\n\n\n"NOR,me);
	//���ǰ����

	me->delete_temp(QUESTDIR3);

	//�趨����ˮ�ϱ��
	me->set_temp(QUESTDIR3+"baohushuisheng",1);

	return 1;

}
//������


int do_qiang(string arg)
{
	object me = this_player(), ob;
	
	if (!me->query_temp(QUESTDIR3+"baohushuisheng")) return notify_fail("��������ˮ������¶������ˣ�����ʲôӢ�ۣ�\n");

	if (arg != "��" && arg !="dao") return notify_fail("��Ҫ����ʲô��\n");
	
	if (me->is_busy())
		return notify_fail("���Ѿ���æ�����У��㻹��ɶ����\n");
	if (me->query_temp(QUESTDIR3+"qiangdao"))
		return notify_fail("���Ѿ������ˣ�����ɶ����\n");
	
	
	
	me->set_temp(QUESTDIR3+"qiangdao",1);

	ob = present("xuedao laozu", this_object());
	
	if (!ob) 
	{
		return notify_fail("Ѫ�����涼���ˣ��㻹��ɶ����\n");
	}
	message_vision(HIW"$N��$nͬʱ����ȥ�����С�$N�������£��Ȱ����˵�����\n"NOR, me, ob);
	message_vision(HIC"$n����˫�֣�����$N���ж�ȥ��$Nһ����Ϣ���ſ���Ѫ�������ֳų֡�\n"NOR, me, ob);
	message_vision(HIC"$n֪���Լ������޶࣬��һ��������$N�������Լ�����ɥ$N�֡�\n"NOR, me, ob);
	message_vision(HIC"$Nͷ����$n��ס������Խ��Խ���ѣ��ؿ��������ѡ�\n\n"NOR, me, ob);
	me->start_busy(100);
	call_out("story3", 3+random(3), me, ob);
	return 1;
}


void story3(object me, object ob)
{
	
	if (me->query_skill("shenzhao-jing", 1) < 550) 
	{
		tell_object(me,HIC"�������վ��ȼ�����550��,��δ�ڻ��ͨ���޷���ζ�����⾳��\n"NOR);
		call_out("finish", 1, me);
		return;
	}
	tell_object(me, RED"����л����ŵ�һ�����������ϳ壬Ҫ�ӿڱ��к��˳���������ͷ��Ҫ�����裬������嵽��ͷ���ֻ�����ȥ��\n"NOR);
	tell_object(me, RED"һ�������������������ͻ������������ʼ���Ҳ�����·��\n"NOR);
	tell_object(me, HIM"��ֻ��ȫ�����������ѴＫ�㣬����ֻ�У����ҿ�Ҫ���ˣ��ҿ�Ҫ���ˣ���\n\n"NOR);
	tell_object(me, HBYEL+HIW"�ڴ������ǹصĹؼ�ʱ�̣����Ȼ�������򣬽���һ������ľ��磬��Щ�����ϵĸо���\n\n"NOR);
	tell_object(me, HIG"������һ�ߣ������������ȴ��֫���������п񺰣����ҿ�Ҫ���ˣ���\n\n"NOR);
	
	call_out("story4", 3+random(3), me, ob);
}

void story4(object me, object ob)
{
		object shui,diyun;

		shui=present("shui sheng",environment(me));
		if (!me) return;
	
		if (!shui) 
		{
			
			return notify_fail("�����Թ�ۻ㣬ǰ�����������޹أ����������죬Ҳû��һ���˾���\n����Ӧ�þ���֮��ȴ���㱣�����������ɣ���Ү��Ү����\n");
		}
		if (!ob) 
		{
			
			return notify_fail("Ѫ�����涼����ɱ�ˣ�����ô����ȥ����\n");
		}

		tell_object(me, HIM"��ʱˮ���ۼ����Σ�����������Ǳ����������У���\n\n"NOR);
		
		tell_object(me, HIY"Ѫ������һʱ�����΢һ���䣡��ˮ��ŭĿ���ӣ��ȵ��������ӣ��ѵ����ң���\n"NOR);

		message_vision(HIC"$N���ڵľ���������ǿ������ȴ����ʮ�ֺ��£�ֻ����������˫����ץ���裬ʼ����\n"
							"����$n���ϣ��������ҳż��£�ͻȻһ������$n��С������֮�ϡ�\n\n"NOR, me, ob);
		message_vision(HIR"Ѫ������һ���Һ�����ʱ���Ե��ء�\n\n"NOR, me, ob);
		ob->unconcious();

		tell_object(me, RED"ˮ��ΪѪ�����淽��һ�ţ�����һ�ţ����е�����ס��˳�Ƶ���������\n"
				+"�������ڻ����ڵ�Ѫ������Ĳ����ϣ��ǵ������쳣����ʱ��Ѫ�����������촦����\n"NOR);
		ob->die();
		
		me->start_busy(1);

		message_vision(HIY"$N���������ض�ˮ��˵�����������߰ɣ�����Ѫ����������һ������Ź���ġ�\n"NOR, me);

		message_vision(HIY"$n˫ĿãȻ��äĿ�ص��ͷ��˵�����������ˣ�ȫ�����ˣ���\n"NOR, me, shui);
		message_vision(HIG"$n˵�������������ȥ��\n\n"NOR, me, shui);
		message_vision(HIC"����Ҳ���׷�˳�ȥ��\n\n"NOR, me, shui);
		if (shui)
			destruct(shui);
		if (diyun)
			destruct(diyun);
		message_vision(HBYEL+HIW"��ϲ�㣬������ɡ����Ǿ���֮��ѩɽ����ƪ���½ڹ������ݣ�\n"NOR,me);
		message_vision(HBYEL+HIW"ʣ�µĹ������Ǿ��书�����վ��񹦡��Ĳ�����������Ժ��ڴ˲��ϲ����ˣ�\n"NOR,me);
		message_vision(HBYEL+HIW"�����Ǿ������书֮����Ӱ��ȭ�����ֽ�½�����ţ�\n"NOR,me);
		me->set(QUESTDIR3+"over",1);
		return;
	
}
/*
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
}*/
/*
*/

int do_canwu(string arg)
{
	int i,j,x;
	object*obj;
	object me=this_player();

	obj = users();
	x = sizeof(obj);
	
	while(x--) {
		  if ( obj[x]->query_temp("quest/szj/shenzhao/canwu")
			  && obj[x]!=me
			  && environment(me)==environment(obj[x]))
			 {
				  message_vision(HIY"$N��ͼ�������վ��񹦣�ȴ����"+obj[x]->query("name") +HIY"�Ѿ����Ķ���������ֻ�������ڶ���Ⱥ�\n"NOR,me);	
				  me->move("d/xueshan/xuegu2");
				  return 1;
			}
			
	}

	if (!arg||arg!="���վ���")
	{
		return notify_fail("��Ҫ����ʲô�񹦣�\n");
	}

	if (!me->query(QUESTDIR3+"over") )
	{
		return notify_fail("����δ��ɡ����Ǿ���֮������ƪ���½ڹ������ݣ�\n");
	}
	if (me->query_skill("shenzhao-jing",1)<550)
	{
		return notify_fail("���վ�����550���޷��ڻ��ͨ��\n");
	}
	
	if (me->query("quest/szj/pass")==3 || me->query("quest/shenzhao/laozu"))
	{
		return notify_fail("���Ѿ��⿪�����⣡\n");
	}

	if ((time()-me->query(QUESTDIR+"time"))<86400)
	{
		return notify_fail("���Ѿ������ˣ�����������\n");
	}
	if( (string)me->query("gender") == "����" )
		return notify_fail("ʩ�������ȱ���������Ե��ͣ��޷��������վ��߼�������\n");
	
	if (me->query_temp("quest/szj/shenzhao/canwu"))
	{
		return notify_fail("�����ڲ������վ���֮��!\n");

	}
	if (me->is_busy())
		return notify_fail("���Ѿ���æ�����У��޷�����\n");

	if (this_object()->query("shenzhao/canwu"))
	{
		return notify_fail("�꣡�������ڲ������վ���֮�У��������!\n");

	}

	message_vision(HIW"$Nƽ�ľ������滺���������ǽ�ڣ���Ŀڤ�룬���뵱�������沫���䷢����һĻĻ�龰��\n"NOR,me);
	message_vision(HIW"$N���Լ��ܷ��ٴν�����������ľ���������\n"NOR,me);

	me->set_temp("quest/szj/shenzhao/canwu",1);
	me->start_busy(99);
	
	this_object()->set("canwu/shenzhao",1);

	remove_call_out("thinking");
	call_out("thinking",1,me);
	return 1;
}
//�����ж�
// ��������42����Դ�������

int thinking(object me)
{
	int i,j,k; 
	if(!me) return 0;
	
	k=random(me->query("kar"));
	j=20;
	i=me->query("int");

	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	
	if(me->query_temp("shenzhao_cw")<(15+random(10)))
    {  
	  me->add_temp("shenzhao_cw",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n�������ǰ����һƬ�������ޣ����������������.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n����ϸ��ĥ������ת�ļ��ɣ��ƺ���Щ�ĵá�\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n��һʱ�������꣬���������ת��û���ƺã����߻���ħ��Σ�գ�\n"NOR);
			 me->add_temp("shenzhao_cw",-2);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ������²����ڻ��������룬�ƺ������ĵ�.\n"NOR);
			me->add_temp("shenzhao_cw",1);

			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ���������.\n"NOR);
			me->add_temp("shenzhao_cw",-1);

			break;
		case 5:
			tell_object(me,MAG"\n�����һ�ᣬ�������ȣ����ĺܣ��ƺ�����ԼԼ����һ˿��⣡\n"NOR);
			me->add_temp("shenzhao_cw",3);

			break;

		default:tell_object(me,YEL"\n���ĸ����꣬������ڤ.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"��ϥ����������ʯ�ڣ���������\n"NOR, ({}));

	  call_out("thinking",3+random(3), me);

   } 
   else if (k>27
	  && random(j)<2
	  && random(i)>41
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 tell_object(me, HIW"ͻȻ֮�䣬��ֻ���ظ�����Ҵ�ʹ�����������Խ��Խ��Խ��Խ�ȣ�������������\n"
						"û�г��ڣ�ֱҪ�Ѹ������������ǰ������֮��ġ�����Ѩ�����ƺ�������������һ��С\n"
						"�ף���ʱ������˿˿�����ӡ�����Ѩ��ͨ����׵ĩ�˵ġ���ǿѨ��ȥ����������������\n"
						"ǿ����Ѩ��಻�����磬������������������������ǿ��ȴ�Ƕ�������������Ϣ������ͨ��\n"
						"�����ڵ���Ϣ�����޷���й��һ�ɾ޴�����������ײ��������Σ��������ǿ���͹�������\n"
						"��ͨ�������Ͷ����Ĵ��ѹء�����Ϣһͨ�롰��ǿѨ������ʱ�����ᡢ���ء����š�����\n"
						"��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������\n"
						"��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
	
		tell_object(me, HIY"�����Ϣ�嵽�ٻ�Ѩ�У�ֻ��������һ��������һ�������Ӷ�ͷ���������ڴ�������ͨ��\n"
						"�˴��µġ��н�Ѩ������н�Ѩ������������һ���Զ����Ρ�������Ѩ�����������棬��\n"
						"����������Ϣһ·���У�����Ȫ����ͻ������ᡢ���ǡ��Ϲ������á����С���ͥ���β��\n"
						"���ڡ����ϡ��С������䣬����ˮ�֡����ʡ�������ʯ�š���Ԫ���м���������Ѩ���ֻ�\n"
						"���ˡ�����Ѩ�������һ�������н�����������֮��ȫ����˵�����ĳ������á���Ϣ��һ\n"
						"��ͨ��ʱ���Ǽ��ѣ��ζ�������ͨ����·���ˣ��ڶ��Ρ�������ʱ��Ȼ��Ȼ�ķɿ���ת��\n"
						"���֮�䣬������һʮ�˴Ρ�\n\n"NOR);
		message("channel:rumor", MAG"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ���ʹ���վ���ͨ���ζ��������ﵽ�����վ��ķ�����߾��磡\n"NOR, users());
		message("channel:rumor", MAG"��ҥ�ԡ�ĳ�ˣ���ϲ"+me->query("name")+"�⿪���վ������ھ����书���Ӵ���ظ�����\n"NOR, users());

         message_vision(HIW"\n$N���д�ϲ�����������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N����������ĥ�����������������վ������ε��书��Ҫ�����վ����˴�ɣ���\n"NOR,me);
		 
         log_file("quest/shenzhaojing", sprintf("%s(%s) ���վ������似���ܳɹ���ʧ�ܵ�%d�κ���򣬻�Ե�ɺ��£���ǰ�������ֵ��%d,��ǰ���ֵ��%d,��ǰ��������ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query(QUESTDIR3+"fail"),
		 k,
		 j,
		 i,
         me->query("combat_exp"),
		 ));

		 me->set(QUESTDIR+"time",time());
		 me->delete_temp("shenzhao_cw");
		 me->delete_temp("quest/szj");
		 this_object()->delete("canwu");

		 me->set("quest/szj/pass",3);
		 me->set("quest/shenzhao/laozu",1);//��������
		 
		 me->set("title",HBMAG+HIW"���Ǿ�*������"NOR);
		 me->set("mytitle/quest/szj3",HBMAG+HIW"���Ǿ�*������"NOR);
		 me->start_busy(1);
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵���������������վ������ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HBYEL+HIW"\n�ǳ��ź����������վ��񹦵����ν���ʧ�ܣ�\n"NOR,me); 
         log_file("quest/shenzhaojing", sprintf("%s(%s) ʧ�����վ��񹦲��򣡵�%d��ʧ�ܣ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ��������ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query(QUESTDIR3+"fail"),
		 k,
		 j,
		 i,
         me->query("combat_exp"),));        
		 
		 me->add(QUESTDIR3+"fail",1);
		 me->set(QUESTDIR+"time",time());
		 me->start_busy(2);
		 me->delete_temp("shenzhao_cw");
		 me->delete_temp("quest/szj");
		 this_object()->delete("canwu");
		 me->start_busy(1);
		 return 1;
   }



}