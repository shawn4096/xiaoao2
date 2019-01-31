
#include <ansi.h>
inherit ROOM;
//#include "/d/thd/niujia/npc/sdyxz.h";
#define QUESTDIR "quest/���Ӣ�۴�/"
#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"

int do_move(string);
int do_turn(string);
int story_1(object me);
int do_jiaoliang(object me);
int confirm(object me);
int yg_come(object me);
void create()
{
	set("short", "С�Ƶ�");
	set("long", @LONG
����һ���Ѿ������˵�С�Ƶ꣬��̨�ϻ����˻ң�һ�����������һ���
�ɲݣ��Ա�б����һ�������棻��̨��ĳ��������ҵط��ż����ƾɵ��໨��
��(wan)������ǰ����һ�����ų�����С���
LONG
	);

	set("item_desc", ([
		"wan" : "һ�Ѻ����ҵ�ɢ���ŵ��롣\n",
		"bowl" : "һ�Ѻ����ҵ�ɢ���ŵ��롣\n",
		"tiewan" : "һֻ��ֵ��룬�����ǹ̶����˼����ϡ�\n",
		"ironbowl" : "һֻ��ֵ��룬�����ǹ̶����˼����ϡ�\n",
	]) );

	set("exits", ([
		"north" : __DIR__"njroad1.c",
	]));

	set("objects", ([
		__DIR__"npc/shagu.c":1,
		__DIR__"npc/qusan.c":1,
		"/d/baituo/npc/ouyangke.c":1,
	]));

	setup();
}

void init()
{
	object me,nv1,nv2,ke;
	me=this_player();
	add_action("do_move","move");
	add_action("do_move","yi");
	add_action("do_turn","turn");
	add_action("do_turn","zhuan");
	add_action("do_jiaoliang","jiaoliang");
	
	if (me->query_temp("slbw/story1"))
	{
	   if (!present("ouyang ke",this_object()))
	   {
		   ke=new("/d/baituo/npc/ouyangke.c");
	       ke->move("/d/thd/niujia/xiaodian");
		   ke->set("jiali",50);
		   ke->set("str",20);
	   }
	  if (!objectp(nv1=present("shao nv",this_object())))
	  {
		   nv1=new("/d/baituo/npc/baiyishaonv");
		   nv1->move("/d/thd/niujia/xiaodian");
	   }
	 
	   //nv2=new("/d/baituo/npc/baiyishaonv");
	   //nv2->move("/d/thd/niujia/xiaodian");
	   message_vision(HIC"ŷ������Ц������̧ͷ��������˵������������λ���ѣ��������ˣ��β����������\n"NOR,me);
	   
	   call_out("story_1",3,me);

	}
	//����������ĳ���
	if (me->query_temp(QUESTDIR1+"askguo") 
		&& me->query(QUESTDIR+"start")
		&& me->query_temp(QUESTDIR1+"start"))
	{
		
		message_vision(CYN"$N������������С�ƹݣ������ܴ���һ�£�ֻ��һ�����Ӻ����ų��ʣ�һ�ԵľƵ��ϰ���������æµ�š�\n"NOR,me);
		message_vision(CYN"$N����������������������˵��������ң��������Ϻõ��׾ơ���\n"NOR,me);

		call_out("yg_come",3+random(4),me);
		me->delete_temp(QUESTDIR1+"start");
		me->delete_temp(QUESTDIR1+"askyang");
		me->delete_temp(QUESTDIR1+"askguo");
		//me->set_temp(QUESTDIR1+"");
		return ;
	}
}

int do_move(string arg)
{
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("����æ���أ�\n");
	if (arg == "wan" || arg == "bowl") {
		write("�㽫�����ϵ���ʹ����ˤ������ȥ��ȴ������һֻ�뾹Ȼ�ò���������ϸһ�����ŷ�������һֻ����(tiewan)��\n");
		me->set_temp("mishi_temp",1);
		return 1;
	}
	return notify_fail("��Ҫ�ᶯʲô��\n");
}

int do_turn(string arg)
{
	int temp;
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("����æ���أ�\n");
	if (arg == "tiewan left" || arg == "tiewan zuo") {
		temp = me->query_temp("mishi_temp");
		if (!temp) return 0;
		if (temp < 4) temp++;
		else temp = 1;
		write("�㽫�����þ�������⶯�������ˡ���֨����������\n");
		me->set_temp("mishi_temp",temp);
		return 1;
	}
	if (arg == "tiewan right" || arg == "tiewan you") {
		temp = me->query_temp("mishi_temp");
		if (!temp) return 0;
		if (temp > 3) temp++;
		else temp = 1;
		write("�㽫�����þ������Ұ⶯�������ˡ���֨����������\n");
		if (temp == 7) {
			write("ֻ����������һ�����죬�����ǰ������һ���š��������ԥ�����˽�ȥ��\n");
			message("vision", "���ܺ����Ȼ�ֳ�һ�����ţ�" + me->name() + "�ٲ����˽�ȥ������֨ѽѽ���ֹ����ˡ�\n", this_object(), me);
			me->delete_temp("mishi_temp");
			me->move(__DIR__"mishi");
			message("vision", me->name() + "�򿪰��ţ����˽�����\n", environment(me), me);
		}
		else me->set_temp("mishi_temp",temp);
		return 1;
	}
	return notify_fail("��Ҫ��ʲô��\n");
}

int story_1(object me)
{
   object li,ke;
   if (!objectp(li=present("li sheng",environment(me))))
   {
	    li=new("/kungfu/class/gaibang/lisheng.c");
        li->move("/d/thd/niujia/xiaodian");
   }
   else
	   li=present("li sheng",environment(me));
   message_vision(HIW"����ǽͷ�ݽǵ�$N֪���ѱ��������ŷ���˲�ͷ����µĲ�������һ�ۣ���Ц�������벻�����˶��Ĵ����ô�����뵽��\n"
   +HIC"\nŷ���˻�����ǰ��������ӣ����۳�һ������ģ����$N�����������ƺ���ɫ������һ����֪���ѿ��Ʋ����в��ŵ��ˣ���Ҫʹ�¶��֡���æ�н�\n"
   +"���п�����ö���룬ֻ�����������䣬���̷�������������������������������д����֦���������ŷ���˱��ķ�ȥ��ԭ��ؤ������\n"
   +"Ҳ�ѿ����������գ��ȶ������֡�\n"
   +HIB"\n\n\nŷ���˷������֣�ʳָ����ָ��סһ��������ָ��Сָ��ס��һ�����������죬��֦�̼��۳����Ľء�Ⱥؤ������˹����޲���Ȼ�������˽е�����\n"
   +"��ʦ�壬�����ա�������δ�ϣ��͵�һ�����죬������Ȼ˺���������ɵ���������������������ŵع��������Ų���һ����������ǰ���漴Ծ��\n"NOR,me);
  
   ke=present("ouyang ke",environment(me));
   if (!objectp(ke))
     return 0;
   li->kill_ob(ke);
   me->delete_temp("slbw/story1");
   me->set_temp("slbw/keli",1);
   return 1;  

}

int do_jiaoliang(object me)
{
	object ke;
	me=this_player();
	if (objectp(present("hong qigong",environment(me))))
	 return notify_fail("���߹��Ѿ��ڳ������õ���������ŷ���˽�����\n");
	ke=present("ouyang ke",environment(me));
	if(file_name(environment(me))!="/d/thd/niujia/xiaodian" ) 
         return 1;
	if (!objectp(ke))
	   return 0;
	//ke->add_temp("apply/damage",-50);
    //ke->add_temp("apply/attack",-150);
	
	if (me->query("quest/gb/xlz/slbw/pass"))
	    return notify_fail("������Ѿ��⿪����Ҫ�Ѿ��ˡ�\n");
	if (time()-me->query("quest/gb/xlz/slbw/time")<86400)
	    return notify_fail("������Ѿ�����һ�Σ���24Сʱ������\n");
	if (ke->is_busy())
	   return notify_fail("ŷ��������æµ��������æ�˲������㣿\n");
	if (!me->query_temp("slbw/keli"))
	   return notify_fail("ŷ���˺�����û��ս���������Ǵ��Ķ����ģ�\n");   
	
	if (me->query_skill_mapped("strike")!="xianglong-zhang"||me->query_skill_prepared("strike")!="xianglong-zhang")
	  return notify_fail("��û�м��������ƣ���κ�ŷ���˽�����\n");   
	
	if (objectp(ke)&&me->query_temp("slbw/keli"))
	{
		ke->kill_ob(me);
		message_vision(HIY"$N�ȵ�����ŷ���������������ɸ����ҽ���һ������˵����ʹ����ʮ���Ƶ���ʽ�ͺ�ŷ���˶���һ��\n",me);
        message_vision(HIB"ŷ������Ц��������ƾ���Ǽ�������è�Ĺ���Ҳ�Ҹ��Ҷ��������Ҿ������ʶ��ʶ������ѧ������������\n",me);
		message_vision(HIG"$Nת�ۼ����˲�����ʮ���У�$N�Ѱ�ʮ������������ʹ���˼��飬�㹻�Ա�����ŷ�����书ʵ�߳�\n"
		+"�����࣬Ҫ��ȡʤ��ȴҲ���ܡ��ٶ�ʮ���У�ŷ����ȭ�����䣬ǰ�ܺ�Ծ��������������Ѹ��֮����\n",me);
	     		  
		  //me->set_temp("slbw/fightke",1);
          remove_call_out("confirm");
	      call_out("confirm", 20, me);
		  message_vision(HIB"\n\n\nŷ�������ڼ���֮�У���Ȼ��һ�����Լ���������֮�£���ʱԾ�����ȵ������󱲰��㹫��ү�����ֵĹ����������������\n"
		                   +"����δ�ϣ�ͻ����ͷ������΢�죬��Ҫ���ܣ����������úÿ죬��֪���������к�Ȼ����һ���ͷ�Ͼ�����Щ��ζ��\n"
						   +"ŷ�����־��ֿ֣���æ�³�������һ�鼦�ǡ�ŷ���˾�����̧ͷ�쿴��ֻ������һ�ѻҳ���ͷ���䣬æ����Ծ�����۵�һ������\n"
						   +"���ֶ���һ�鼦�ǡ����ȴ��һ�鼦�ȹǣ�ֻײ�������������ۡ�\n"NOR,me);
        	
		return 1;
	}

}

int confirm(object me)
{
   
    object ob,hong,li,nv;
	int i,j,t;
	
	ob=present("ouyang ke",environment(me));
	li=present("li sheng",environment(me));
	nv=present("shao nv",environment(me));
	//girl1
	//if (!me->query_temp("slbw/fightke"))
	  // return notify_fail("��û���������߹��Ľ̻壬���ŷ���ˣ��Ͻл������ʧ����\n");   
	if (!objectp(hong=present("hong qigong",environment(me))))
	{
	  hong=new("kungfu/class/gaibang/h7g.c");
	  hong->move(environment(me));
	 }
	//else hong=present("hong qigong",environment(me));
	
	message_vision(CYN"\n\nһ����Ӱ������ƮȻ���䣬������������Ҫ����ָ��$N����׽�ߵ���ʽ���ѵ���ʰ����$n�����С����?\n"NOR, me,ob);
	message_vision(HIG"\n\n$Nֻ���ú��߹����Լ������������Լ����⽵��ʮ����������еİ��һ���ǡ���˪�����������С��������졯������ǡ�������β����\n"
			+"��Щ��ʽһһ�̸���$N�����ֻ�����߹�˵�����Ȱ���С�Ӵ����˵��\n"NOR,me);
	//i=random(15);
	j=random(me->query("kar"));
	t = 20;
    if(me->query("m-card-vip")) t =  18;
    if(me->query("y-card-vip")) t =  15;
    if(me->query("buyvip"))     t =  10;
	i= random(t);
	
	if (me->query("kar")<31
		&&j>26
		&&i<3)
	{
       message_vision(HIC"\n\n$N���ڽ��������������ѧȫ���ڻ��ͨ������������$n�мܲ�ס������������ȥ�����߹���֮Ҳ��̾һ����Ȼ��ȥ��\n"NOR,me,ob);
	   message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ�ѧȫ����ʮ���ƣ������ƴﵽ����������ľ��磡\n"NOR, users());
	   message("channel:chat", HIC"�����졿���߹���"+me->query("name")+"�����ұ�ؤ�����յ���һλ������ӣ������λ���������Ժ����ˡ���\n"NOR, users());
	   message("channel:chat", HIC"�����졿���߹���ؤ�ｵ��ʮ����������������Ե����Ʒ�����\n"NOR, users());
	   message("channel:chat", HIC"�����졿���߹�����а���������ϵۡ���ؤ������ͨ���������������ͽ����ǧ���������Ҵ�ؤ������磡\n"NOR, users());
		if (objectp(ob))
			destruct(ob);
	    if (objectp(hong))
			destruct(hong);	
		if (objectp(li))
			destruct(li);
		if (objectp(nv))
			destruct(nv);
	   //me->add("combat_exp",15000);
	   log_file("quest/xlzslbw",sprintf("%s(%s) �ں�ŷ����ս���󣬵õ����߹�������ָ�㣬����ŷ���ˡ���Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/slbw/fail"),me->query("combat_exp"),me));
	   me->set("title",HIC"��ؤ"HIR"����ʮ���ƴ���"NOR);
	   me->set("quest/gb/xlz/slbw/pass",1);
	   me->delete_temp("slbw/keli");
	   return 1;
	}
	else
	{
		message_vision(HIY"\n\n$N��Ȼ�����߹�˵�������������У����������ʹ�õľ�������һʱ֮��ȴ��������⡣����ʮ���Ƶ�\n"
		+"������û�з��ӳ����������㻹���д������¸����߹�ѧϰ�ˡ����߹����������ۣ���֮Ҳ��̾һ����Ȼ��ȥ��\n"NOR,me,ob);
		log_file("quest/xlzslbw",sprintf("%8s%-10s�ں�ŷ����ս���󣬵õ����߹�������ָ�㣬����û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/slbw/fail"),me->query("combat_exp"),me));
		message("channel:chat", HIC"�����졿���߹���̾һ�����ƺ���"+me->query("name")+"����ʧ������\n"NOR, users());
		me->add("quest/gb/xlz/slbw/fail",1);
		me->set("quest/gb/xlz/slbw/time",time());
		me->delete_temp("slbw/keli"); 	
		if (objectp(ob))
			destruct(ob);
	    if (objectp(hong))
			destruct(hong);	
		if (objectp(li))
			destruct(li);
		if (objectp(nv))
			destruct(nv);
        return 1;
	}     
     return 1;
}


//���Ӣ�۴����
//�����ĺ͹�Х�����С��
int yg_come(object me)
{
	object yang,guo;
	message_vision(HIW"\n\n�����ѩ�׷ɣ��캮�ض������̲�ס���˸����£������Ĵ�����֮�ʡ�\n"NOR,me);
	message_vision(HIY"����ᣬ������������ˬ�ʵ���������������磬����һ��Ⱦƣ�\n"NOR,me);
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		yang=new("d/thd/niujia/npc/yang");
		yang->move("d/thd/niujia/xiaodian");
	}
	if (!objectp(yang=present("guo xiaotian",this_object())))
	{
		yang=new("d/thd/niujia/npc/guo");
		yang->move("d/thd/niujia/xiaodian");
	}
	me->set_temp(QUESTDIR1+"ygcome",1);
	add_action("do_hejiu","hejiu");

}
int do_hejiu()
{
	object me,yang,guo;
	me=this_player();
	
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		return notify_fail("�����Ĳ��ڴ˵أ������޷����������ͷ������\n");
	}
	if (!objectp(guo=present("guo xiaotian",this_object())))
	{
		return notify_fail("��Х�첻�ڴ˵أ������޷����������ͷ������\n");
	}
	if (me->query_temp(QUESTDIR1+"hejiu"))
	{
		return notify_fail("��������Ĺ�Х�췽�Ų���һ��ȹ��ƣ���\n");
	}
	message_vision(HIC"$N����Ʊ��������ĺ͹�Х��˵�����������ڴ�С�Ƶ���ż����λӢ�ۣ�ʵ��������������������\n"NOR,me);
	message_vision(HIC"$N˵�������캮�ض����Ҿ���λһ������\n"NOR,me);
	message_vision(HIY"��ʱ�����ĺ�Ȼ˵������������㿴��ǰ���Ǹ������书���ס���\n"NOR,me);
	message_vision(HIC"$n˵�������������Ƚ��ң�Ҳ��֪�����Ǻ��˻��ǻ��ˣ���Զ�۴������ɱ��������С��Ϊ���\n"NOR,me,guo);/**/
	tell_object(me,HIY"������˵������Ҫ�ǻ������ѵ����ǻ����������ɣ�����\n"NOR);
	
	me->set_temp(QUESTDIR1+"hejiu",1);
	me->set(QUESTDIR1+"hejiu",1);
	call_out("qiu_come",3+random(2),me);
	return 1;
}

int qiu_come(object me)
{
	object qiu,yang,guo,bing;
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		return notify_fail("�����Ĳ��ڴ˵أ������޷����������ͷ������\n");
	}
	if (!objectp(guo=present("guo xiaotian",this_object())))
	{
		return notify_fail("��Х�첻�ڴ˵أ������޷����������ͷ������\n");
	}	
	if (!objectp(qiu=present("qiu chuji",this_object())))
	{
		qiu=new("d/thd/niujia/npc/qiuchuji");
		qiu->move("d/thd/niujia/xiaodian");
	}
	if (!objectp(bing=present("jin bing",this_object())))
	{
		bing=new("d/thd/niujia/npc/jinbing");
		bing->move("d/thd/niujia/xiaodian");
	}
	qiu->kill_ob(bing);
	bing->kill_ob(qiu);
	me->delete_temp(QUESTDIR1+"ygcome");

	message_vision(WHT"\n\n$N��Զ��һ��������Х֮�䣬ԶԶ����һ�����ˣ�\n"NOR,me);
	message_vision(WHT"\n\n$N�ǵ������ں�һ�������˶�ս��\n"NOR,me);

	message_vision(HIC"$n˵������������һλ���֣��㿴������֮�ʣ�����ֻ����ǳǳ��һ���ӡ�����ѵ��Ǵ�˵�е�̤ѩ�޺ۡ���\n"NOR,me,guo);
	message_vision(HIC"$n���Ǹ�����˵�������캮�ض�����λ�����ɷ�һ���һ������\n"NOR,me,yang);
	message_vision(HIC"�������룬�����Ҳ��ˬ��֮�ˣ����������еİ�����������һ�ţ����ɱ���������Ⱦͺȣ��ѵ��һ����������˶಻�ɣ���\n"NOR,me,yang);
	add_action("do_check","chakan");
	add_action("do_check","check");
	return 1;
}
int do_check(string arg)
{
	object me,yang,guo,qiu;
	me=this_player();
	if (!arg||arg!="����") return notify_fail("��Ҫ�鿴ʲô��\n");
	
	if (!me->query_temp(QUESTDIR1+"hejiu"))
	{
		return notify_fail("��û��һ��ȹ��ƣ��˴˶�����Ϥ���ҷ����˰����ܲ���ò��\n");
	}

	if (me->query_temp(QUESTDIR1+"chakan"))
	{
		return notify_fail("���Ѿ��鿴��һ�α����ˣ��ҷ����˰����ܲ���ò��\n");
	}
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		return notify_fail("�����Ĳ��ڴ˵أ������޷����������ͷ������\n");
	}
	if (!objectp(guo=present("guo xiaotian",this_object())))
	{
		return notify_fail("��Х�첻�ڴ˵أ������޷����������ͷ������\n");
	}
	if (!objectp(qiu=present("qiu chuji",this_object())))
	{
		return notify_fail("�𴦻����ڴ˵أ������޷����������ͷ������\n");
	}
	if (qiu->is_fighting())
	{
		return notify_fail("�𴦻�����ս������û�а����а��������������޷��鿴�������\n");
	}
	message_vision(HIR"\n\n$N���Ǹ��������������ϵİ������Ǻ��棬��ϸһ����������һ����ͷ������������˿˿���Ѫ����\n"NOR,me);
	message_vision(HIC"�����ĺ͹�Х��Ҳ��������������쳣�����Ǹ����˺ȵ�����������������ʲô��������\n"NOR,me);
	message_vision(HIG"$n���Ǹ�����˵�������ߣ���Ȼ��һ��֮�ѣ��������������ɣ�����\n"NOR,me,yang);
	
	qiu->fight_ob(yang);
	qiu->fight_ob(guo);
	qiu->hit_ob(me);
	//�鿴����
	me->set_temp(QUESTDIR1+"chakan",1);


	call_out("do_fight1",10+random(3),me);
	return 1;
}

int do_fight1(object me)
{
	message_vision(HIG"\n\n�𴦻���Ȼ�ȵ�����ͣ������Ȼ���������˵����������ʹ�õ������ǹ�����ѵ�����Һ��˲��ɣ���\n"NOR,me);
	message_vision(CYN"�������ۼ���һ����ᣬ��æ���ܵ��������������������в����գ���������Ԫ˧���´������˺�����������Ҳ��\n"NOR,me);
	message_vision(CYN"������Ȼ��ָ��ָ��Х���ܵ�������λ���ҽ����ֵܣ���ɽ�ú���ʤ���˹�Х�죬�������´�硱\n"NOR,me);
	message_vision(CYN"�������ʵ���������������ȫ�潣������·��Ϊ�������ɱ��Խ���Ĺ�������\n"NOR,me);
	message_vision(MAG"�𴦻���Ȼ����֪�����´����ش���ᣬ���ǽ��͵������������ǽ����϶������һ·׷ɱ���ˣ������и�ͬ��Ѿ��������ˣ�׷�����ˣ���\n"NOR,me);
	message_vision(HIG"���˻�Ȼ����֪����һ����ᣬ���ŵĽ��֣����ɵر˴˼�������ϧ���ֿ�ʼ���������\n"NOR,me);
	//qiu->remove_enemy();
	call_out("go_home",4+random(3),me);
}
int go_home(object me)
{
	object yang,guo,qiu;
	if (!me) return 0;

	message_vision(HIY"\n\n�ƹ���Ѳ���˹���ζ���˴˼�Ӣ��ϧӢ��\n�������ĺ͹�Х���ʢ�������£������������ļ��м����Ⱦƣ�\n"NOR,me);
	me->set_temp(QUESTDIR1+"xiangzhi",1);
	me->set(QUESTDIR+"xiangzhi",1);
	
	if (objectp(yang=present("yang tiexin",this_object())))
		destruct(yang);
	if (objectp(guo=present("guo xiaotian",this_object())))
		destruct(guo);
	if (objectp(qiu=present("qiu chuji",this_object())))
		destruct(qiu);
	
	return 1;
}