// attacker.h for hs job
#include <ansi.h>
int do_move(string arg);

void init()
{
	object me;
	me=this_player();
	if (!me->query("quest/xd/jglts/jingang/pass"))
	{	
		tell_object(this_player(),WHT"\n����ѩ���У�������Щ����.\n"NOR);
		
	}else tell_object(this_player(),WHT"\n����ѩ���У������������Ȼ��ɣ�����˿�����������ѡ�\n"NOR);
	
	if (this_player()->query_temp("xd/xgjz"))
	{
		tell_object(this_player(),YEL"\nע�⣺ѩ�������˸��֣����Բ��ܴ���һ���̶��ط���\n"
	+"������Ҫ����ǰ�����ң�east,south,north,west���ƶ���move����Ѱ�ҵ��˲���֮ɱ����\n"NOR);
	}
	if (this_player()->query("killer"))
	{
		tell_object(this_player(),"\nע�⣺���ֲ��ܽ���˵ء�\n");
		this_player()->move("d/");

	}
	if (this_object()->query("xueceng")>2 && !me->query("quest/xd/jglts/jingang/pass"))
	{
		tell_object(this_player(),YEL"\n�˵ؿ�����Ϊϡ�����������Щ���ơ�\n"NOR);
		if (!this_player()->query_condition("xuegu_bieqi"))
		{
			this_player()->apply_condition("xuegu_bieqi",5);
		}
	}
	add_action("do_tanting","tanting");
	add_action("do_tanting","ting");
	add_action("do_move","move");
	add_action("do_lianti","lianti");
}

int do_move(string arg)
{
	object me;
	int i;
	me=this_player();
	i=this_object()->query("xueceng");
	
	if (me->is_busy())
	{
		return notify_fail("������æµ�У�\n");
	}
	if (!arg)
	{
		return notify_fail("��Ҫ���Ǹ������ƶ�?\n");
	}
	switch (arg)
	{
		case "east" :
			tell_object(me,YEL"��˫�����ٴ��ڣ��������ƶ�������!\n"NOR);
			me->add_temp("xuegu/east",1);
			me->move(__DIR__"sxuegu"+i+"1");
			me->start_busy(1);
			break;
		case "west" :
			tell_object(me,WHT"��˫�����ٴ��ڣ����������ƶ�������!\n"NOR);
			me->add_temp("xuegu/west",1);
			me->move(__DIR__"sxuegu"+i+"2");
			me->start_busy(1);

			break;
		case "north" :
			tell_object(me,CYN"��˫�����ٴ��ڣ��������ƶ�������!\n"NOR);
			me->add_temp("xuegu/north",1);
			me->move(__DIR__"sxuegu"+i+"3");
			me->start_busy(1);

			break;
		case "south" :
			tell_object(me,MAG"��˫�����ٴ��ڣ����������ƶ�������!\n"NOR);
			me->add_temp("xuegu/south",1);
			me->move(__DIR__"sxuegu"+i+"4");
			me->start_busy(1);

			break;	
		
		case "up" :  //ÿ�����л����ж���������ʱ����
			
			if (this_object()->query("zuan"))
			{
				tell_object(me,HIW"�㷢�ִ˴�ѩ������������϶���ƺ���������������ѩ��!\n"NOR);
				tell_object(me,HIW"Ѱ�������ֳɵ�����ѩ����������ȥ!\n"NOR);
				if (this_object()->query("xueceng")==1)
				{
					//me->delete_temp("xd");
					//me->delete_temp("xuegu");
					me->move("d/xuedao/xuegu1");	
					tell_object(me,HIC"��������ѩ�ȣ����¿������������̰������������!\n"NOR);
					if (me->query_temp("xd/xgjz_job") && me->query_temp("xuegu"))
					{
						tell_object(me,HIR"����ѩ�ȼ�ս�����Ѿ�ɱ���Ϸ��Ĵ����ɵ����ţ����Կ��ǻ�ȥ�����ˣ�\n"NOR);
						//tell_object(me,HIR"���Ѿ�ɱ�ˣ�\m"NOR);
					}
				}
				if (this_object()->query("xueceng")==2)
					me->move("d/xuedao/sxuegu10");			

				if (this_object()->query("xueceng")==3)
					me->move("d/xuedao/sxuegu20");			
				if (this_object()->query("xueceng")==4)
					me->move("d/xuedao/sxuegu30");			
				//me->delete_temp("xuegu");
			}					
			else tell_object(me,HIR"�������ϰ��˰ǣ�ѩ�����Ҽ�Ӳ�����ָ����޷�����!\n"NOR);	
			me->delete_temp("xuegu/north");
			me->delete_temp("xuegu/east");
			me->delete_temp("xuegu/west");
			me->delete_temp("xuegu/south");

			me->start_busy(1);
			break;	
		case "down" :
			if (this_object()->query("zuan"))
			{
				tell_object(me,HIW"�㷢�ִ˴�ѩ������������϶���ƺ���������������ѩ��!\n"NOR);
				tell_object(me,HIW"Ѱ������·����������ȥ!\n"NOR);
				if (this_object()->query("xueceng")==1)
					me->move("d/xuedao/sxuegu20");	
				if (this_object()->query("xueceng")==2)
					me->move("d/xuedao/sxuegu30");			

				if (this_object()->query("xueceng")==3)
					me->move("d/xuedao/sxuegu40");			
				if (this_object()->query("xueceng")==4)
					tell_object(me,HIR"�������°��˰ǣ���ָ�����˼�Ӳ�ĵ��棬�޷�����������!\n"NOR);
				//me->delete_temp("xuegu");
			}
			else tell_object(me,HIR"�������°��˰ǣ�����ѩ�������쳣��Ӳ�����ָ����޷�����!\n"NOR);	
			me->delete_temp("xuegu/north");
			me->delete_temp("xuegu/east");
			me->delete_temp("xuegu/west");
			me->delete_temp("xuegu/south");

			me->start_busy(1);
			break;	

		default:
			tell_object(me,HIC"��˫�����ٴ��ڣ��������˰����ֻص���ԭ��!\n"NOR);
			
			if (this_object()->query("xueceng")==1)
				me->move(__DIR__"sxuegu10");
			else if (this_object()->query("xueceng")==2)
				me->move(__DIR__"sxuegu20");
			else if (this_object()->query("xueceng")==3)
				me->move(__DIR__"sxuegu30");
			else if (this_object()->query("xueceng")==4)
				me->move(__DIR__"sxuegu40");
			else me->move(__DIR__"xuegu");
			//����뿪�������ʱ���
			me->delete_temp("xuegu/north");
			me->delete_temp("xuegu/east");
			me->delete_temp("xuegu/west");
			me->delete_temp("xuegu/south");
			
			break;
	}
	me->add_busy(1);
	return 1;
}

int do_tanting()
{	
	object me,ob;
	me=this_player();
	tell_object(me,me->query("name")+CYN"������������ϸ�۲���Χ�Ķ���!\n"NOR);
	
	if (!me->query_temp("xd/xgjz_job")) return notify_fail("����������ѩ�������㾲������\n");
	
	
	
	if (random(me->query_temp("xuegu/north"))>=2
		&&random(me->query_temp("xuegu/east"))>=2
		&&random(me->query_temp("xuegu/west"))>=2
		&&me->query_temp("xd/xgjz_job")
		&&random(me->query_temp("xuegu/south"))>=2)
	{
		switch (query("xueceng"))
		{
			case 1:
				if (me->query_temp("xuegu/lutianshu")) break;
				
				message_vision(YEL"ͻȻ,$N����ǰ��ѩ����һ����Ϣ���������ƺ���������������ƶ�����!\n"NOR,me);
				message_vision(HIR"$N��������������ս����ʱ��ֻ��ǰ����ѩ��һ��Ķ���һ��������ѩ���˶�Ȼ����������ǰ!\n"NOR,me);
				
				ob=new("d/xuedao/npc/lutianshu");
				
				ob->set_name("½����", ({ me->query("id")+"\'s lutianshu","lu" }));
				//ob->set("id",me->query("id")+"\'s lutianshu");
				ob->do_copy(me);
				ob->move(environment(me));
				ob->set_temp("target", me->query("id"));

				ob->kill_ob(me);
				
				me->set_temp("xuegu/lutianshu",1);
				break;
			case 2:
				if (me->query_temp("xuegu/huatiegan")) break;

				message_vision(HIG"ͻȻ,$N����ǰ��ѩ����һ����Ϣ���������ƺ���������������ƶ�����!\n"NOR,me);
				message_vision(HIR"$N��������������ս����ʱ��ֻ��ǰ����ѩ��һ��Ķ���һ��������ѩ���˶�Ȼ����������ǰ!\n"NOR,me);
				ob=new("d/xuedao/npc/huatiegan");
				//ob->set("id",me->query("id")+"\'s huatiegan");
				ob->set_name("������", ({ me->query("id")+"\'s huatiegan", "hua" }));
				ob->do_copy(me);

				ob->move(environment(me));
				ob->set_temp("target", me->query("id"));
				ob->kill_ob(me);
				me->set_temp("xuegu/huatiegan",1);

				break;
			
			case 3:
				if (me->query_temp("xuegu/liuchengfeng")) break;
				message_vision(HIY"ͻȻ,$N����ǰ��ѩ����һ����Ϣ���������ƺ���������������ƶ�����!\n"NOR,me);
				message_vision(HIR"$N��������������ս����ʱ��ֻ��ǰ����ѩ��һ��Ķ���һ��������ѩ���˶�Ȼ����������ǰ!\n"NOR,me);
				ob=new("d/xuedao/npc/liuchengfeng");
				ob->set_name("���з�", ({ me->query("id")+"\'s liuchengfeng","liu" }));
				//ob->set("id",me->query("id")+"\'s liuchengfeng");
				ob->do_copy(me);

				ob->move(environment(me));
				ob->set_temp("target", me->query("id"));
				
				ob->kill_ob(me);
				me->set_temp("xuegu/liuchengfeng",1);

				break;

			case 4:
				if (me->query_temp("xuegu/shuidai")) break;
				
				message_vision(HIY"ͻȻ,$N����ǰ��ѩ����һ����Ϣ���������ƺ���������������ƶ�����!\n"NOR,me);
				message_vision(HIR"$N��������������ս����ʱ��ֻ��ǰ����ѩ��һ��Ķ���һ��������ѩ���˶�Ȼ����������ǰ!\n"NOR,me);
				ob=new("d/xuedao/npc/shuidai");
				ob->set_name("ˮ�", ({ me->query("id")+"\'s shuidai", "shui" }));
				//ob->set("id",me->query("id")+"\'s shuidai");
				ob->do_copy(me);

				ob->move(environment(me));
				ob->set_temp("target", me->query("id"));
				
				ob->kill_ob(me);
				me->set_temp("xuegu/shuidai",1);
				break;

			default:
				me->move(__DIR__"xuegu");
			break;
		}
		//me->delete_temp("xuegu");
		tell_object(me,WHT"��˫�����ٴ��ڣ����������ƶ�������!\n"NOR);
	}
	me->start_busy(1);
	return 1;
}

//�������������


int do_lianti()
{
	object me,weapon;
	me=this_player();
	if (!me) return 1;
	
	
	if (me->query_skill("xuedao-jing",1)<350)
	{

		return notify_fail("��Ѫ��������350����ô����Ҳ����Ҫ�죡\n");
	}
	if (me->query("family/family_name")!="Ѫ����")
	{
		return notify_fail("�㲻��Ѫ���ŵ��ӣ�������ǲ������ô��\n");
	}

	if (me->query("quest/xd/jglts/jingang/pass"))
	{
		
		return notify_fail("���Ѿ��⿪��������⣬����Ե�޹���������������\n");
	}


	if (time()-me->query("quest/xd/jglts/jingang/time")<86400)
	{
		//command("say ��");
		return notify_fail( "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n");
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		return notify_fail( "Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ���ǵմ������ܴ�����߼��书����\n");
	}
	if (me->query_temp("quest/xd/jglts/jingang/lianti"))
	{
		return notify_fail("������������!\n");

	}
	if (!me->query_temp("quest/xd/jglts/jingang/start"))
	{
		return notify_fail("��û�еõ�������ķ����ں�ָ�㣬��ѩ���б����˰���Ҳ����Ҫ�죡\n");
	}

	message_vision(HIY"$N��ʹ���洫�ڵ��������ţ�ͷ���£����Լ�������������ѩ���У�ֻ����˫��¶�����棡\n"NOR,me);
	me->set_temp("quest/xd/jglts/jingang/lianti",1);
	me->start_busy(2);
	me->delete_temp("quest/xd/jglts");
	//remove_call_out("do_lianti");
	call_out("do_lianxi",1,me);
	return 1;
}

int do_lianxi(object me)
{
   int i,j,jobs; 
	if(!me) return 0;
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	

   jobs=(int)me->query("job_time/Ѫ������")+(int)me->query("job_time/Ѫ������");
   if(me->query_temp("canwu_lianti")<(10+random(10)))
   {  
	  me->add_temp("canwu_lianti",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n�㽫�Լ�ͷ����ѩ�У���ס��������ʱ��Ѫ��ӿ.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n����ϸ��ζѪ������ת�ļ��ɣ���Ȼ��Щ���ƣ����������ܡ�\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n��һʱ�������꣬���������ؿڣ�ǿ�н�һ����Ѫ������ȥ��..\n"NOR);
			 me->add_temp("canwu_lianti",-3);
			break;
		case 3:
			tell_object(me,HIW"\n��ͷ���£���˳�����������澭�������ƺ������ĵ�.\n"NOR);
			me->add_temp("canwu_lianti",1);

			break;
		case 4:
			tell_object(me,CYN"\n����Ѫ�Ҵܣ��˴��������ؼ�ʱ��.\n"NOR);
			me->add_temp("canwu_lianti",-1);

			break;
		case 5:
			tell_object(me,MAG"\n��������ת���⣬�پ���Ѫ��ӯ������������������.\n"NOR);
			me->add_temp("canwu_lianti",2);
			me->add("qi",me->query("max_qi"));
			me->add("neili",me->query("max_qi"));
			me->improve_skill("jingang-liantishu",me->query_int(1)*10);
			me->improve_skill("xuedao-jing",me->query_int(1)*10);

			break;

		default:tell_object(me,YEL"\n��ͷ���£��������գ�����һ�������״̬.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"ͷ���£�����ѩ�У�ֻ����˫��¶�����棬���ƹ��죬���罩ʬ.\n"NOR, ({}));

	//  remove_call_out("do_mo");
	  call_out("do_lianxi",3+random(3), me);

   } 
  else if (i>25
	  && random(j)<4
	//  && random(jobs)>1200
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$Nԭ����Щ��������������Ѫ��Ȼ������ˮ����ģ��������澭����֮�С�\n"NOR,me); 
         message_vision(HIW"\n$N���ж�ʱ��ϲ�����������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N����������ϰ��������������Ѫ�����������ڵĽ���������İ��أ���\n"NOR,me); 
         log_file("quest/xdjglts", sprintf("%s(%s) ������������ܳɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ������������������İ��أ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/jglts/jingang/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/jglts/jingang/time",time());
		 me->set("quest/xd/jglts/jingang/pass",1);
		 me->delete_temp("canwu_lianti");
		 me->delete_temp("quest/xd/jglts");
		 me->delete_temp("quest/xd/jglts/jingang/lianti");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵�������������������������ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n����������������������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xdjglts", sprintf("%s(%s) ʧ�ܣ���������������%d��ʧ�ܣ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/jglts/jingang/fail",1),
		 i,
		 j,
         me->query("combat_exp"),));        
		 me->add("quest/xd/jglts/jingang/fail",1);
		 me->set("quest/xd/jglts/jingang/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_lianti");
		 me->delete_temp("quest/xd/jglts");
		 me->delete_temp("quest/xd/jglts/jingang/lianti");
		 return 1;
   }
	
}
