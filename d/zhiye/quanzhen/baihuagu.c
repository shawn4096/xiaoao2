#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIM"�ٻ���"NOR);
        set("long", @LONG
ͻȻ����ǰһ�������������ȣ���׺�Ż����ϡ���� ��׵��ʻ���
��һ·��������ز��ǻ�ѩ��������Ţ���˴����ǻ� ��һ�����硣������
��ů��������������֮���磬�紵����һƬ����Ϯ�������˳���ɽ��
�ͱ��Կ����������֡��ٻ��ȡ���������һ������é���ݡ�
LONG                           
        );

        set("exits", ([
				"enter" : __DIR__"maocaowu",
                "south" : __DIR__"huajing3",
        ]));
        set("outdoors", "quanzhen");
        setup();
}

int init()
{
	object me=this_player();
	object yang;
	add_action("do_bishi","bishi");
	if (me->query_temp("quest/shendiao/��ѩ�����/askyangzhou"))
	{
		if (!objectp(yang=present("yang guo",environment(me))))
		{
			yang=new("d/quanzhen/npc/yang");
			
			 if(!clonep(yang)) {
				 destruct(yang);				 
			 }
			
			yang->move(this_object());
		}
		message_vision(HIY"\n\n�����$N΢΢һЦ��˵����������ǰٻ��ȣ��㺰��ɤ������ͯ���ԣ���\n"NOR,me);

		add_action("do_han","han");

	}
}

int do_han(string arg)
{
	object me=this_player();
	object zhou,room,yang;
	if (me->query_temp("quest/shendiao/��ѩ�����/zhouok",1))
		return notify_fail("����ץ��ʱ������ѧ��\n");
	
	if (!arg ||(arg!="����ͯ"&& arg!="�ܲ�ͨ"))
	{
		return notify_fail("��ɽ���ȣ���Ϲ��ʲô��\n");
	}
	
	if (me->query_temp("quest/shendiao/��ѩ�����/hanzhou")) return notify_fail("�ܲ�ͨ�Ѿ������ˣ��㻹��ɶ��\n");
		
	
	me->add_busy(3);
	
	if (!objectp(yang=present("yang guo",environment(me))))
	{
		if (!present("yang guo",room))
				{
				    yang=new("d/quanzhen/npc/yang");
					
				}
				yang->move(environment(me));
	}

	if (arg=="����ͯ" || arg=="�ܲ�ͨ")
	{
		message_vision(HIY"$N��ɽ���д󺰣�������ͯ~~~~���Һ��������ͬ�����˰�����\n"NOR,me);
		room=load_object("d/quanzhen/maocaowu");
	
		if (!objectp(zhou=present("zhou botong",room)))
		{
			if (!objectp(zhou=present("zhou botong",this_object())))
			{
				if (!present("zhou botong",room))
				{
				    zhou=new("kungfu/class/quanzhen/zhou");
				}
				
			}
			
		}
		zhou->move("d/quanzhen/baihuagu");		
		message_vision(HIC"����ͯ���˸��������ӻ��������˳���������Ц����������������?\n"NOR,me);
		//me->delete_temp("quest/shendiao/��ѩ�����");
		me->delete_temp("quest/shendiao/��ѩ�����/askyangzhou");		
		me->set_temp("quest/shendiao/��ѩ�����/hanzhou",1);
		call_out("do_say1",2+random(3),me,zhou,yang);
	}
	return 1;
}
int do_say1(object me,object zhou,object yang)
{
	message_vision(HIC"$N��$n˵�����������������ȥ��һ����ȥ����Ҳ���ȥ��\n"NOR,me,zhou);
	zhou->zhou_say1();
	message_vision("\n\n$N��$n˵�����ѵ������˴����ͷ�����ڵ�Ϧ����Ҳ�����������ô����\n",me,zhou);
	zhou->zhou_say2();
	message_vision(HIG"$N˵��������ʵ����˵�˰գ�����˼����Ľ����������Ҫ��ȥ���� һ�ᡣ��\n"NOR,me);
	message_vision(HIR"$n����˫����ҡ��˵������ǧ�����������£������ݹ��ҷ������飡��\n"NOR,me,zhou);
	message_vision(HIR"\n\n�����$nЦ��������������ǲ�����͸��������ˣ�����\n"NOR,me,zhou);
	
	zhou->fight_ob(yang);
	yang->fight_ob(zhou);
	call_out("check_fight",1,me);
	return 1;
}

int check_fight(object me)
{
	object zhou,yang;
	yang=present("yang guo",this_object());
	zhou=present("zhou botong",this_object());
	if (!zhou||!yang)
	{
		return notify_fail("����NPC������ܲ�ͨ�����ֳ�\n");
	}
	if (objectp(zhou=present("zhou botong",this_object()))&&zhou->is_fighting())
	{
		call_out("check_fight",1,me);
		return 1;
	}
	if (zhou->query_temp("last_damage_from")!=yang)
	{
		return notify_fail("�ܲ�ͨ˵��������ȥ����ȥ�����ǲ�ȥ��������ȥ������ɱ���ң���\n");
	}
	
	message_vision(HIC"\n$N˵������Ȼ�����ƹ�Ȼ�˵ã��������Ҳ��ȥ��\n"NOR,zhou,me);
	message_vision(HIY"\n$n˵����$N�ѵ��㲻��ȥ���������ô����\n"NOR,zhou,me);
	message_vision(HIC"\n\n\n$N���һ���������ӣ����ҵĶ��ӣ������Ķ��������ȥ����\n"NOR,zhou,me);
    //destruct(zhou);
	zhou->move("d/quanzhen/maocaowu");
	me->delete_temp("quest/shendiao/��ѩ�����/hanzhou");
	me->set_temp("quest/shendiao/��ѩ�����/zhouok",1);
	
	if (me->query("gender")=="Ů��") 
	{		
		message_vision(HIY"\n\n$N��$n˵�������ˣ�����һλŮ�ԣ�����ȥ������ȥ�ɣ�����û��ʲô���ˣ���\n"NOR,yang,me);
		return 1;
	}
    if (me->query("gender")=="����")
	{
		message_vision(HIY"\n\n$N��$n˵������Ҫ����ϸ�ˣ�Ҫ���Ĺ���"HIR"(guanwu ��Ȼ������)"HIY",���ʧ��������\n"NOR,yang,me);
		add_action("do_guanwu","guanwu");
		return 1;
	}	
	return 1;
}

int do_guanwu(string arg)
{
	object me=this_player();
	me->start_busy(3);
	if (!arg || arg!="��Ȼ������")
	{
		return notify_fail("��Ҫ����ʲô��\n");
	}
	if (me->query_temp("guanwu_anranzhang"))
	{
		return notify_fail("�����ڹ�����Ȼ���У��԰����ꣿ\n");
	}
	
	if (me->query("gender")!="����")
	{
		return notify_fail("�Ǵ������ԣ��޷���ϰ��Ȼ�ƣ�\n");
	}
	if(me->query("quest/anran/pass"))
	{
		return notify_fail("���Ѿ��⿪�����⣬����ǲ����ͯ�������ô��");
	}
	if(me->query("quest/anran/fail")>=3 && me->query("registered")<3)
	{
		return notify_fail("�Ѿ���δ��ڣ�����ô����û������,�湻���ģ���");
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("quest/anran/time")<86400)
	{	
		return notify_fail("�����Ƚ̵�����ɣ�����ɡ���\n");
	}
	if(me->query_skill("force",1)<450)
	{
		return notify_fail("��Ȼ����Ҫ������������Ļ����ڹ�����450������������\n");
	}
	//һ��Ҫ�ȵ�25���
	me->set_temp("guanwu_anranzhang",1);
	//call_out("check_fight",25,me);	

	me->set("quest/anran/time",time());
	me->set("quest/anran/combat_exp",me->query("combat_exp")); 
	me->start_busy(999);
	call_out("thinking",1,me);
	
	return 1;
}

int thinking(object me)
{
  int i,j,total;
  object zhou,yang;
  
	yang=present("yang guo",this_object());
	zhou=present("zhou botong",this_object());
  if(!me) return 0;
	
  if(me->query_temp("anran/guanwu")<(3+random(3)))
    { 
	  me->add_temp("anran/guanwu",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ������ʩչ��Ȼ�Ƶ�һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("anran/guanwu");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  if (me->query("family/family_name")=="��Ĺ��")
	     i=random(j-3);
	  else i= random(j);
 

    if(i<4 && random(me->query("kar"))>25)
	 {
		tell_object(me,HIG"\n�㰴�������ָ�㣬����Ȼ�����Ƶ����������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"����Ϣ���ԡ���ǿѨ������������ᡢ���ء����š�����\n+"+
"��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������\n"+
"��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
		tell_object(me,HIY"\n��ϲ�㣡������ǧ����࣬���ڵó���Ը��ϰ�þ���<<��Ȼ������>>��\n"NOR);
       	me->set("quest/anran/pass",1);
		me->set("title",HBBLU+HIW"*��Ȼ����*"NOR);
		me->set("mytitle/quest/arztitle",HBBLU+HIW"*��Ȼ����*"NOR);
		me->start_busy(1);
		log_file("quest/anranzhang", sprintf("%8s(%8s) ʧ��%d�κ󣬳���������Ȼ�����Ƶľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/arz/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/anran/fail",1);
		me->set("quest/anran/time",time());
		me->delete_temp("guanwu_anranzhang");

		tell_object(me,HIY"\n\n�����������ָ�㣬��Ȼ��������Ȼ�����Ƶİ��أ����Ƕ����Ʒ�����������ȫȻ����Ҫ�졣\n\n"NOR);
		tell_object(me,HIG"\n\nϣ���ٽ������������ܶ���\n\n"NOR);
		me->start_busy(1);
		log_file("quest/anranzhang", sprintf("%8s(%8s) ��Ȼ�����ƽ���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/arz/fail"),i,me->query("combat_exp")) );
	  }
    	 
  }
  //me->delete_temp("anran");
  me->start_busy(1);
  if (objectp(yang)) {
	 message_vision(HIC"�����Хһ���������ȥ��\n"NOR,me);
	 destruct(yang);
  }
  if (objectp(zhou))
  {
	 // destruct(zhou);
	 zhou->move("d/quanzhen/maocaowu");
  }
  
	return 1;
}
