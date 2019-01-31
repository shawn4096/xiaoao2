#include <ansi.h>
inherit FBROOM;

int     do_cry();
#include "fuben.h";

void create()
{
                                        
        set("short", HIW"��ɽ����-����"NOR);
        set("long", @LONG
����һ���˼�������ɽ�����������ﻬ��ɽ���վ�������һ��̤�գ��Ʊ�
������������е��÷������,�ഫ��ɽ�۽����ڴ˴���ɽ���Ͽ����ĸ����֣�д��
����ɽ�۽������ּ��پ�������������ʯ��ֽ����ָ�����Ƶá�
LONG
        );
		
        set("outdoors", "����");
		set("backroom","/d/huashan/sheshen");
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);       
		
		setup();
}

void init()
{
		//object me = this_player();		
        add_action("do_chaikai","chaikai");		
        //me->set("startroom", "/d/city/guangchang");
		::init();
}


int do_cry()
{
        command("cry");       
}


void task_over()
{
	
	set("over",1);
	fuben_reset();
}

int do_chaikai()
{
	object feng,hong;
	object me=this_player();
	feng=present("ouyang feng",environment(me));
	hong=present("hong qigong",environment(me));
	if (!feng)
	{
		call_out("task_over",1,me);
		return notify_fail("������ֲ𲻼�ʱ��ʹ��ŷ���汻���߹�ʧ��ɱ��������ʧ��!\n");		
	}
	if (!hong)
	{
		call_out("task_over",1,me);
		return notify_fail("������ֲ𲻼�ʱ��ʹ�ú��߹���ŷ����ʧ��ɱ��������ʧ��!\n");		
	}
	feng->remove_all_killer();
    
	tell_object(me,HIC"\n\n������²��ã���æ���Ĵ�����,Ѱ�Ҳ𿪵Ļ�Ե����,���㿴��һ��С�����ϲ��\n\n"NOR);
	tell_object(me,HIC"������һ�����ɣ��ߵ�����֮����ϥ���£��˹���סȫ��һҧ����������������\n\n"NOR);
	tell_object(me,HIC"��֮����ȥ����һ����Ȼ�������������˵������������ϴ���������������һ����\n\n"NOR);
	tell_object(me,HIC"����жȥ��ԭ��ǿ��֮ĩ���ܴ�³�ɣ���ؤ������Ȼ���ǵ���֮�ۣ������Ķ�ʱ��\n\n"NOR);
	tell_object(me,HIC"���Ѿ����޶ࡣ\n"NOR,me);
	feng->set("neili",0);
	feng->start_busy(999);
	hong->set("neili",0);
	hong->start_busy(999);
	//ؤ����ӽӿ�
	if (me->query_temp("wugou/askguo"))
	{
		hong->hong_say();
		add_action("do_yanlian","yanlian");
	}
	//��󡹦�ӿ�
	if ( me->query("oyf/hamagong") == 2)
	{
		feng->feng_say();
		add_action("do_yanshi","yanshi");
	}
	return 1;
}
int do_yanlian(string arg)
{
	object me=this_player();
	object hong,feng;
	feng=present("ouyang feng",environment(me));
	hong=present("hong qigong",environment(me));
	if (!arg || arg!="�����޹�")
	{
		return notify_fail("��Ҫ����ʲô��");
	}
	if (!me->query_temp("wugou/answerok"))
	{
		message_vision(HIC"\n$n��$N�Ȼһ̾�����¶�����ǿ�󣬼�Ȼ�㲻Ը�⣬��ô�Ͻл������ž���������ʧ���ˣ�\n"NOR,me,hong);
		return 0;
	}
	if (me->is_busy()||me->is_fighting())
	{
		return notify_fail("������æµ��!\n");
	}
	message_vision(HIC"\n\n$n�ȵ����϶���һ���һ��ѹ��׵��书û��ʩչ���������벻���ʶ�£���\n"NOR,me,hong);
	message_vision(HIG"$n�ȵ������Ź���������ؤ�ﲻ��֮�أ����������޹�����˼�Ǵ���һ�����������еĹ������������������㣡\n"NOR,me,hong);
	message_vision(HIG"$n�ȵ�����Ȼ������϶������㣡˵�꣬$n�̲�סһ���Ц,����ȴ�����ޱȡ�\n"NOR,me,hong);
    hong->hong_say2();
	message_vision(HIR"\n\n$nһ�����г��֣���ʱ����˷���Ϊ��Ӱ��������ɫ�������޲ߣ�����ڤ���ƽ�֮�С�\n"NOR,me,feng);
	hong->hong_say3();
	if (me->query_skill("dagou-bang",1)< 500)
		return notify_fail("��Ĵ򹷰����ȼ�̫���ˣ�500��Ҫ���޷��������ż��ܡ�\n");
	if (me->query("family/family_name")!="ؤ��")
		return notify_fail("�㲻��ؤ���ӵܣ�����Ī���ǽ���ļ�ϸô��\n");
	if (me->query("family/master_name")!="���߹�")
		return notify_fail("�㲻�Ǻ��߹���ү�ӵ��״����ӣ�����������\n");
	if (me->is_busy())
	{
		return notify_fail("��������æ���ң�\n");
	}

	if (me->query("quest/gb/dgb/wugou/pass"))
		return notify_fail("���Ѿ��⿪�����޹����⣬����������\n");
	if (me->query_temp("wugou/yanlian"))
		return notify_fail("���������������޹����������У�\n");

	if ((time()-me->query("quest/gb/dgb/wugou/time"))<86400)
		return notify_fail("������̫�ڿ��ˣ��´�������\n");
	if (me->query("int")<40)
		return notify_fail("�򹷰���Ҫ���ߵ����ԣ�����������������˴򹷰��ģ�\n");
	if(me->query("quest/gb/dgb/wugou/fail")>=3 && me->query("registered")<3)
	{
		tell_object(me,"�Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		return 1;
	}
	me->start_busy(99);
	call_out("thinking",1,me,hong,feng);
	return 1;
}

int thinking(object me,object hong,object feng)
{
   int i,j;

  if(me->query_temp("wugou/yanlian")<(10+random(5)))
  { 
	  me->add_temp("wugou/yanlian",1);
      if(random(2)) tell_object(me,HIY"\n����������ŷ��ź��߹���ŷ����ս������չ�ֵ�һ��һʽ...\n"NOR);
             else tell_object(me,HIG"\nͻȻ�䣬���ƺ�ץ�����������޹��Ĺؼ�...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
   }
   else
   {  
	  me->delete_temp("wugou/yanlian");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  18;
      if(me->query("buyvip"))     j =  15;
	  i= random(j);	
     
	if(i< 2
		&& random(me->query("int"))>40
		&& random(me->query("kar"))>28)
	 {
		tell_object(me,HIY"\n\n���������ã���Ȼ���Ȼ���ʣ������޹�����ʽ�����������ݺ����أ�\n��ϲ������ǧ����࣬���ڵó���Ը�����������޹�����ʽ�ڻ��ͨ! \n"NOR);
       	me->set("quest/gb/dgb/wugou/pass",1);
		me->set("title",HIY"ؤ��"HIR"�������޹�"NOR);
		me->set("quest/gb/dgb/wugou/time",time());
		me->set("mytitle/quest/txwgtitle",HIY"ؤ��"HIR"�������޹�"NOR);
		me->start_busy(1);
		log_file("quest/dgbwugou", sprintf("%8s(%8s) ʧ��%d�κ󣬳��������޹�������iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/gb/dgb/wugou/fail"),i,me->query("combat_exp")) );
		set("over",1);
	   fuben_reset();
	 }
	 else
	 {
		me->add("quest/gb/dgb/wugou/fail",1);
		me->set("quest/gb/dgb/wugou/time",time());
		 
		tell_object(me,HIY"\n\n�����˺��߹���ָ�㣬��Ȼ�����������޹��İ��أ����Ƕ԰�����κ���ʽ�ڻ��ͨ����������ȫȻ����Ҫ�졣\n\n"NOR);
		tell_object(me,HBBLU+HIW"\n\n���������޹�����ʧ�ܣ��ٽ�������\n\n"NOR);
		me->start_busy(1);
		me->delete_temp("wugou");
		log_file("quest/dgbwugou", sprintf("%8s(%8s) �򹷰������޹�����ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/gb/dgb/wugou/fail"),i,me->query("combat_exp")) );
	}
	message_vision(HIY"\n\n����Ӷ�������������Ȼ���֣�����һƬ�ž���\n"NOR,me);
	tell_object(me,HIR"\n\nŷ����ͺ��߹�������Ȼͬʱί���ڵأ�˫Ŀ���գ��������ң�һ��Ҳ�����ˡ�\n\n"NOR);
	tell_object(me,HIR"ԭ�������Ѻľ��������������������·�֮ǰ���ɸ�̾��\n\n"NOR);
	tell_object(me,HIR"�常�ͺ�����ǰ����Ȼ���Լ�������С�䰲������˻��룬�����컯Ū�ˡ�\n\n"NOR);
	tell_object(me,HIR"�����ˣ����Ĺ�����»���к�����? \n\n"NOR);
	tell_object(me,HIR"��ؤ������ʮ���������񶷣��������£���֪��ͬʱ�ڻ�ɽ�������졣\n\n"NOR);
	tell_object(me,HIR"\n\n�㳤̾һ������ֻ����Ȼ��ɽ��\n\n"NOR);
	if (objectp(feng)) destruct(feng);
    if (objectp(hong)) destruct(hong);
	me->delete_temp("wugou/yanlian");
	set("over",1);
	fuben_reset();	
    return 1;
  }
}

//��󡹦����ʾָ��

int do_yanshi(string arg)
{
	    object* ppl;
        object me = this_player();
        object hong = this_object();
        object feng;
	      int i, time, total, j, h = 0;

		ppl = users();
		
		i = me->query("combat_exp") - 500000;
		i /= 500000;

		
        feng = present("ouyang feng", environment(me));

         j = sizeof(ppl);      

		while(j--){
			if( userp(ppl[j]) && !wizardp(ppl[j]) && !(ppl[j]->query("no_pk")) && ppl[j]->query("quest/hama/nizhuan/pass") )
			{
			  h++;
			}
          }
		if (h>0)
		{
			return notify_fail("�Բ��������з�ϴ��������ߣ�û�������ˣ�\n");
		}
		if (!arg||arg !="�����ȷ�")
		{
			return notify_fail("��Ҫ�����߹���ʾʲô���£�����ô����\n");
		}
		if (me->query_skill("lingshe-zhangfa",1)< 500)
			return notify_fail("��������ȷ��ȼ�̫���ˣ�500��Ҫ���޷��������ż��ܡ�\n");
		if (me->query_skill("hamagong",1)< 500)
			return notify_fail("��ĸ�󡹦�ȼ�̫���ˣ�500��Ҫ���޷��������ż��ܡ�\n");

		if (me->query("family/family_name")=="ؤ��")
			return notify_fail("ŷ�������ؤ����ӣ�����Ī������ı��ŷ����ô��\n");
		if (me->query("family/family_name")=="������")
			return notify_fail("ŷ������޴�����ӣ�����Ī������ı��ŷ����ô��\n");
		
		if (me->is_busy()||me->is_fighting())
		{
			return notify_fail("������æµ��!\n");
		}
		if (me->query("quest/hama/nizhuan/pass"))
			return notify_fail("���Ѿ��⿪��󡹦��ת���⣬����������\n");
		if ((time()-me->query("quest/hama/nizhuan/time"))<86400)
			return notify_fail("������̫�ڿ��ˣ��´�������\n");
		if (me->query("con")<40)
			return notify_fail("��󡹦��Ҫ���ߵĸ��ǣ����������������˸�󡹦��ת�ģ�\n");
		
		if (me->query_temp("hama/super"))
			return notify_fail("���������������ȷ����������У�\n");
		
		//if(me->query("quest/gb/dgb/wugou/fail")>=3 && me->query("registered")<3)
		//{
		//	tell_object(me,"�Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		//	return 1;
		//}
		//!me->query("oyf_son") || 
		if (me->query("oyf/hamagong") != 2 )
		{
			return notify_fail("�Բ�������δ���ŷ�����ٴδ��ڣ�����������\n");
		}
		me->start_busy(99);
		call_out("thinking_hm",1,me,hong,feng);              
        return 1;
}


int thinking_hm(object me,object hong,object feng)
{
   int i,j;

  if(me->query_temp("hama/super")<(10+random(5)))
  { 
	  me->add_temp("hama/super",1);
      if(random(2)) tell_object(me,HIY"\n����������ŷ��ź��߹���ŷ����ս������չ�ֵ�һ��һʽ...\n"NOR);
             else tell_object(me,HIG"\nͻȻ�䣬���ƺ�ץ��������������Ĺؼ�...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_hm");
	  call_out("thinking_hm",3+random(3), me);
   }
   else
   {  
	  me->delete_temp("hama/super");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  18;
      if(me->query("buyvip"))     j =  15;
	  i= random(j);	
     
	if(i<2
		&& random(me->query("con"))>40
		&& random(me->query("kar"))>28)
	 {
		tell_object(me,HIY"\n\n���������ã���Ȼ���Ȼ���ʣ������������ʽ�����������ݺ����أ�\n��ϲ������ǧ����࣬���ڵó���Ը�����������������ʽ�ڻ��ͨ! \n"NOR);
       	tell_object(me,HIG"ֻ�����常�ͺ���ǰ������һ�ɶ�Զ������ɷ��,���常���ź��߹����书��ǿ������ֱ���Ż�Ҫ�������䡣\n\n"NOR);
		tell_object(me,HIG"�����仰���ú��߹�Ҫ���㡸�򹷰�������������ȥ�������常��ʶ��\n\n"NOR);
		tell_object(me,HIG"ŷ���濴��֮�������̸�����ƽ�֮�������������������߹��������߹����������ƽ⣬�漴�ֽ����µ���ʽ����\n\n"NOR);
		tell_object(me,HIG"���һ��һ������������ʱ����ŷ�����ѽ������˺��߹���ʮ���У����������������֮����\n\n"NOR);
		tell_object(me,HIG"���߹�����е���ߣ��������ġ������޹��������常ڤ˼����˵��:Ϊ������ƽ��ѧ���һ�Դ������㣬�������ƽ��⡸�����޹�����\n\n"NOR);
		tell_object(me,HIG"���߹���ŷ�����ƽ������ġ������޹�����������ǿ���Ű���ŷ�����ǰ�������������������䡣\n\n"NOR);
		tell_object(me,HIG"ŷ���汻��ͻ�������ľٶ�һ������ʱ�����Լ���������ŷ���棬����ǰ�������ϳ�ұ�ؤ���߹���\n\n"NOR);
		tell_object(me,HIG"���ϻ�����ӵ����Ц����\n\n"NOR);
		tell_object(me,HIM"��Ӻ��߹���ŷ�����ս���л����ǳ��\n"NOR,me);
		tell_object(me,HIR"\n\n��ɹ�����常�ĸ�󡹦,��Ĺ�������ˣ�\n"NOR,me);
		me->add("combat_exp",(30000+random(20000)));
		me->add("oyf/hamagong",1);
		me->set("title",HIW"����ɽׯ"BLU"����"HIW"�������"NOR);
		me->set("mytitle/quest/xidutitle",HIW"����ɽׯ"BLU"����"HIW"�������"NOR);
		
		me->set("quest/hama/nizhuan/pass",1);
		me->set("quest/hama/nizhuan/time",time());
		me->start_busy(1);
		log_file("quest/hmgsuper", sprintf("%8s(%8s) ʧ��%d�κ�ѧ����ת����������iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/hama/nizhuan/fail"),i,me->query("combat_exp")) );		
	 }
	 else
	 {
		me->add("quest/hama/nizhuan/fail",1);
		me->set("quest/hama/nizhuan/time",time());
		me->set("oyf/hamagong",2);//��ֹbug
		 
		tell_object(me,HIY"\n\n������ŷ�����ָ�㣬��Ȼ�����������������ת������İ��أ����ǹ����ڻ��ͨ����������ȫȻ����Ҫ�졣\n\n"NOR);
		tell_object(me,HBBLU+HIW"\n\n���������������ת��������ʧ�ܣ��ٽ�������\n\n"NOR);
		me->start_busy(1);
		me->delete_temp("hama/super");
		log_file("quest/hmgsuper", sprintf("%8s(%8s) ��ת������������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/hama/nizhuan/fail"),i,me->query("combat_exp")) );
	}
	message_vision(HIY"\n\n����Ӷ�������������Ȼ���֣�����һƬ�ž���\n"NOR,me);


	tell_object(me,HIR"\n\nŷ����ͺ��߹�������Ȼͬʱί���ڵأ�˫Ŀ���գ��������ң�һ��Ҳ�����ˡ�\n\n"NOR);
	tell_object(me,HIR"ԭ�������Ѻľ��������������������·�֮ǰ���ɸ�̾��\n\n"NOR);
	tell_object(me,HIR"�常�ͺ���ǰ����Ȼ���Լ�������С�䰲������˻��룬�����컯Ū�ˡ�\n\n"NOR);
	tell_object(me,HIR"�����ˣ����Ĺ�����»���к�����? \n\n"NOR);
	tell_object(me,HIR"��ؤ������ʮ���������񶷣��������£���֪��ͬʱ�ڻ�ɽ�������졣\n\n"NOR);
	tell_object(me,HIR"\n\n�㳤̾һ������ֻ����Ȼ��ɽ��\n\n"NOR);
	
	set("over",1);
	me->unconcious();
	me->delete_temp("hama/super");
	fuben_reset();
	
    
	//me->add("quest/hama/super",1);
	//me->set("quest/hama/time", time());
    
    return 1;
  }

}
