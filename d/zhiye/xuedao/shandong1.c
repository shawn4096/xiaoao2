// shandong1.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
int do_kanshou(string arg);
int do_attack(object ob);
int give_reward(object ob);
int do_wanzi(object me);

#include "/d/xuedao/npc/attacker.h"

void create()
{
        set("short","ɽ��");
        set("long",@LONG
Ұ��һ�����ؾ޴�ɽ�������������ɶ��ڴ�����ż������ЩѪ����
��Ϊ���������������ٶ�����ɽ������Ѳ������������ڷ���һ���޴�
��ͭ��(tongding ),һ�Ե�С����������������������Ǵ��������
Ʈ����������ڷ��˲���ľͷ���ӣ������ϰ����˸������ʵ�Ѫ�⣬Ѫ
���ŵ��Ӳ��Ͻ�����������Ѫ���͵�������������������¶����ҩ��
LONG );
        set("exits",([
                "out" : __DIR__"sroad8",
        ]));
        set("objects", ([
                __DIR__"npc/lianyao_lama" :1,
			__DIR__"obj/xueding" :1,
				"/kungfu/class/xuedao/miaoke" :1,
        ]));
		set("item_desc", ([
           "tongding" : "    �����ɻ�ͭ���ɵ�����ͭ������Լ���ٶ��������и��ֲش����\n"+
                             "�ļ���ͼ�������ڻ������������������Ľ�Ҫ��ͷ! Ϊ�˱�����������\n"+
                             "�����ڴ˾���(jingjie)�غ����Ұ�޻���˵��ƻ�͵Ϯ��\n",
        ]));

        setup();
		//set("outdoors", "xuedao");
        replace_program(ROOM);
}
void init()
{
	add_action("do_kanshou","jingjie");
	add_action("do_lianwan","lianwan");

}

//Ѫ����������
//xdjjjob
int do_kanshou(string arg)
{
	
       mapping fam;
       int exp;
       object me;
       object ob = this_player();
	   if (!arg||arg!="ͭ��")
	   {	
		   return notify_fail("��Ҫ����ʲô��\n");
	   }
	   if(!present("miao ke",  environment(ob) ) )
           return notify_fail("����֮�˲��ڣ���Ҫ����ʲô��\n");

       me = present("miao ke",  environment(ob) );
       fam = ob->query("family");
       exp = ob->query("combat_exp");

	   if (!ob->query_temp("xdjj/askmiaoke"))
	   {
		   return notify_fail("�˴���Ѫ����Ҫ�أ�����ͭ����Ҫ�õ���ɵ���ɣ�\n");
	   }

       if(ob->is_busy()) return notify_fail("��������æ���ء�\n");

       message_vision(CYN"$N���ڴ�Э���������Ѫ��������ҩ�����ξ�������\n"NOR,ob);

       if (!fam || fam["family_name"] !="Ѫ����")
             return notify_fail(GRN"��ɸ����㣺"+RANK_D->query_respect(this_player())+"�뱾�������������ҿ����ǲ�����������ˣ�\n"NOR);

       if (exp < 150000)
             return notify_fail("���ʵս���鲻�㣬������ȥ���Ի��Щ����ֵ��˵�ɣ�\n");

       if (exp > 2500000)
             return notify_fail("���Ѿ����Գ����ݺὭ���ˣ�����ȥ������������Ҫ�Ĺ����ˣ���Щ����ͽ�����ʦ�������ɣ�\n");

       if(ob->query("job_name") == "Ѫ������")
		{
            message_vision(CYN"���˵����"+ob->query("name")+"���������Ѫ���������񣬻�����ȥЪϢƬ�������ɣ�\n"NOR,ob);
            return 1; 
		}
	   if(ob->query_condition("job_busy")){
            message_vision(CYN"���˵����"+ob->query("name")+"����������æµ�У�������ȥЪϢƬ�������ɣ�\n"NOR,ob);
            return 1; 
       }

       if (ob->query_condition("xdjj_job"))
             return notify_fail("������ΪѪ���ŵ���Ѳɽ��������\n");

        ob->set_temp("xdjj_job",1);
        ob->set_temp("apply/short", ({RED"Ѫ������"NOR+" "+ob->query("name")+"("+capitalize(ob->query("id"))+")"}));
        message_vision(CYN"���˵�����ðɣ�"+ob->query("name")+"������������ʱ���������ȱ���֡�\n"NOR,ob);
        message_vision(CYN"���˵������ͭ����¯��Ѫ����������Ѫ���书�������֣�ȫƾ��¯���ܡ�\n"
							+"�������˵������������ʿ����֯����͵Ϯ���ɣ�"+ob->query("name")+"��һ��ҪС�Ŀ�����\n"NOR,ob);
        call_out("give_reward",200+random(30),ob);
        ob->add_busy(1);
        ob->set("job_name", "Ѫ������");
		ob->apply_conditon("xdjj_job",20);
		ob->set_temp("xdjj_job",1);
        
        if(random(10) > 5)
		{
			ob->set_temp("xd/xdjj/second",1);
			call_out("do_attack",20+random(20),ob);
		}
		else call_out("do_attack",100+random(60),ob);
			
        return 1;   
}

int do_leave(object ob)
{
        object me;
        ob = this_player();
        me = present("miao ke",  environment(ob));

        if( ob->query_temp("xdjj_job")<1 )
            return notify_fail("�㲢û����ΪѪ�����䡣\n");

        ob->delete_temp("xdjj_job");
        if (!me) return notify_fail("�������ɲ���ʱ͵������ɾ��Բ��С�\n");
			me->add("job_time/Ѫ������",-1);
        if (me->query("job_time/Ѫ������") < 0) me->set("job_time/Ѫ������",0);
        ob->delete_temp("apply/short");
        ob->apply_condition("job_busy",16);//add by caiji@SJ
        // busy must > 15,because of a bug
        ob->apply_condition("xdjj_job",16);// add by caiji@SJ
        //busy must > 15,because of a bug
        message_vision(CYN"$N�����������Ѫ������ͭ��������\n"NOR,ob);
        message_vision(CYN"���˵����������"+ob->query("name")+"����Ȼ��ɲ�����Ҳ����ǿ�㣬�´κúøɰɣ�\n"NOR,ob);
        return 1;
}

int do_attack(object ob)
{
        mapping skills;
        string *sk;
        int exp,i,lv;
        object att;
        if(!ob || !ob->query_temp("xdjj_job")) return 1;
        
		if(!present("miao ke",environment(ob))) {
             tell_object(ob,"Ѫ����������ʧ�ܡ�\n");
			 ob->apply_condition("xdjj_job",8);
             ob->delete_temp("xdjj_job");
             return 1;
        }
        exp = ob->query("combat_exp");
        lv = ob->query("max_pot") - 100;
       //if( ob->query("combat_exp")<500000) lv-=20;
       // else if (ob->query("combat_exp") < 1000000) lv-=15;
       // else if (ob->query("combat_exp") < 1500000) lv-=10;
        
		if (ob->query("combat_exp")<800000)
		{
			lv=lv-30;
		}else if (ob->query("combat_exp")<1000000)
		{
			lv=lv-20;
		}
		else if (ob->query("combat_exp")<1500000)
		{
			lv=lv-10;
		}

        if(lv < 100) lv = 100;

		if (ob->query_temp("xd/xdjj/second")>0)
			i=i+20+random(10);
		att = new(__DIR__"npc/attacker");
		do_copy(ob);

        att->set("qi",(int)ob->query("qi"));
        att->set("max_qi", (int)ob->query("max_qi") );
        att->set("eff_qi", (int)ob->query("max_qi") );
        att->set("jing",(int)ob->query("jing"));
        att->set("eff_jing",(int)ob->query("max_jing"));
        att->set("neili",(int)ob->query("max_neili") );
        att->set("max_neili",(int)ob->query("max_neili") );
        att->set("jingli",(int)ob->query("jingli"));
        att->set("eff_jingli",(int)ob->query("eff_jingli"));
        att->set("combat_exp", exp);
		
		att->set("owner",ob->query("id"));
		att->set("long",att->query("long")+"\n����ר��β��"+ob->query("name")+"���������ͣ�\n");
	  
		skills = att->query_skills();
        
		if (mapp(skills)){
             sk = keys(skills);
             for (i=0;i<sizeof(sk);i++)
             skills[sk[i]] = lv;
        }
		message_vision(HIY"\n�����������˺�������ʦ�֣��ҵ������ǵĳ�Ѩ�ˣ���\n"NOR,ob);
		message_vision(HIC"	��~~~~\n"HIR"	��~~~~\n"HIY"	��~~~~\n"HIW"	ˮ~~~~\n"NOR,ob);
        message_vision(HIR"\n"+ob->query("name")+"������������������һ��"+att->name()+"���Ŷ��룬��$N�������ҵĹ�����\n\n"NOR,ob);
        att->move(environment(ob));
        att->kill_ob(ob);

        return 1;
}

int give_reward(object ob)
{
        int p,e,shen;
        object me,here;

        if (!ob) return 1;
        me = present("miao ke",  environment(ob));
        here=environment(ob);
		
		e = 100 + random(50)+ random(ob->query("combat_exp"))/10000;	
		//e = 200 + random(50)+ random(ob->query("combat_exp"))/10000;	

		ob->delete_temp("apply/short");
		//����ڹ涨ʱ����û����job�򲻸�����
		if(!ob->query_temp("xdjj_job")) return 1;
		
		else if((string)here->query("short") != "ɽ��")
		{
			ob->delete_temp("xdjj_job");
			ob->apply_condition("xdjj_job",2);
			tell_object(ob,CYN"Ѫ������ʱ���ѵ�������"+ob->query("name")+"����ְ�أ�����ʧ���ˣ�\n"NOR);
			return 1;
        }
		else if(present("miao ke",  environment(ob)) 
			&& here->query("short") == "ɽ��")
			tell_object(ob,CYN"���˵����"+ob->query("name")+"��Ѫ����������˳����ɣ�\n"NOR);
		else {    
			message_vision(CYN"���˵�����ã�ʱ�䵽�ˣ�"+query("name")+"������ȥ��Ϣ�ɣ�\n"NOR,ob);
		}
	/*
		e = ob->add_exp_combat(e,"���","Ѫ������");
		
		shen=50+random(50);
		ob->add("shen",-shen);
		ob->add("job_time/Ѫ������",1);
		p = e/5 + random(e/10);
		
		ob->add("potential",p);
		*/
		TASKREWARD_D->get_reward(ob,"Ѫ������",-1,0,0,3 + random(2),0,0,0,"���");

		ob->delete_temp("xdjj");

		if ( (int)ob->query("potential", 1) > (int)ob->query("max_pot", 1))
			ob->add("potential" , ob->query("max_pot", 1));
		if (random(ob->query("job_time/Ѫ������"))>800 && random(ob->query("kar"))>26 && !ob->query("quest/xd/dichuan"))
		{
			
			message_vision(HIC"��ɶ�"+ob->query("name")+"�����˴�Ĵָ��˵�������������飬�������$NΪ��Ѫ�����ĵ��ӡ�\n"NOR,ob);
			ob->set("title","Ѫ���ŵմ�����");
			ob->set("quest/xd/dichuan",1);
		}
		if (ob->query("quest/xd/dichuan"))
		{
			ob->set("title","Ѫ���ŵմ�����");
		}
		
	//	tell_object(ob, GRN"��˴ο��ع��õ�"+CHINESE_D->chinese_number(e)+"�㾭�飬"+CHINESE_D->chinese_number(p)+"��Ǳ��,"+CHINESE_D->chinese_number(shen)+"�㸺��\n"NOR);
	//	log_file("job/xdjingjie",sprintf("%8s%-10sѪ����������%3d�㾭�飬%2d��Ǳ�ܣ��־��飺%d��\n",
	//		ob->name(),"("+ob->query("id")+")",e,p, ob->query("combat_exp")), ob);
		remove_call_out("do_attack");
		ob->apply_condition("job_busy",2+random(2));
		ob->apply_condition("xdjj_job",4);
		ob->delete_temp("xdjj_job");
		ob->delete_temp("guard");
		ob->delete_temp("xd/xdjj");
		return 1;
}
int valid_leave(object me, string dir)
{
        
		if (dir == "out" && me->temp_temp("xdjj_job"))
        {
                message_vision(HIW"\n"+me->query("name")+"������������ݹ������ú���������䣬����͵����\n"NOR, me);
                return notify_fail("�㰲��������ݹ�������ǣ����Ѫ���ŵմ����ӵ���ݣ�\n");
		}
      
        return ::valid_leave(me,dir);
}

int do_lianwan()
{
	object me;
	me=this_player();
	if (!me->query_temp("xd/lianwan/askke"))
	{
		return notify_fail("����Ե�޹ʣ������������ѵ��Ǽ�ϸ��");
	}
	if (this_object()->query("lianwan"))
	{
		return notify_fail("����ͭ�����ڱ�"+this_object()->query("lianwan/name")+"ʹ�ã�\n");
	}
	if (me->query_temp("lianwan_tick"))
	{
		return notify_fail("��ǳ�æµ�����������С�");
	}
	if (me->query_temp("xd/lianwan/start"))
	{
		return notify_fail("���Ѿ���ʼ�����С�");
	}

	this_object()->set("lianwan/name",me->query("name"));
	
	message_vision(YEL"$N�ߵ�ͭ��ǰ���򿪶��ǣ�������Ѫ���������Ѫ�����һ��Ȼ��ĬĬ��һ������ʼ�������������\n"NOR,me);
	me->start_busy(15);
	me->set_temp("xd/lianwan/start",1);
	//remove_call_out("do_wanzi");
	call_out("do_wanzi",1,me);
	return 1;
	
}

int do_wanzi(object me)
{
	int i,j,jobs; 
	object ob;
	if(!me) return 0;
	i=random(me->query_int());
//	j=20;

//	if(me->query("m-card-vip")) j =  18;
//	if(me->query("y-card-vip")) j =  15;
//	if(me->query("buyvip"))     j =  10;
	j=me->query_skill("medicine",1);
	
	jobs=(int)me->query("job_time/Ѫ������")+(int)me->query("quest/xd/lianwan/count");
	
   if(me->query_temp("lianwan_tick")<(15+random(10)))
   {  
	  me->add_temp("lianwan_tick",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n�㽫�ĵ������������յļ�����ʢ.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n�㶦����ð��˿˿������\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n��һʱ�������꣬������Щƫ�󣬼�æ������ѹ��ѹ��..\n"NOR);
			 me->add_temp("lianwan_tick",-2);
			break;
		case 3:
			tell_object(me,HIW"\n�㼯�о�������סͭ����������ʼ����.\n"NOR);
			me->add_temp("lianwan_tick",1);

			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ���������.\n"NOR);
			me->add_temp("lianwan_tick",-2);

			break;
		case 5:
			tell_object(me,MAG"\n�㹦��Ԫת���⣬Ѫ��֮�о�ȻƮ����Ũ��������.\n"NOR);
			me->add_temp("lianwan_tick",3);

			break;

		default:tell_object(me,YEL"\n�������Ȼ�Ѫ���������죬Ѫ�⿪ʼѪ������.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"�㼯�о�����סѪ�������鼫Ϊרע...\n"NOR, ({}));

	  call_out("do_wanzi",3+random(3), me);

   } 
  else if (i>30
	  && random(j)>80
	  && random(jobs)>200
	  && random(me->query("kar"))>15
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIC"\nѪ���д�ʱѪ�����ڣ�����Ũ��֮������һ¯������¶������Ҫ���ˡ���\n"NOR,me); 
         message_vision(HIW"\n$N���д�ϲ�����������������Ц������˵������������\n"NOR,me); 
		 if (random(10)>5)
		 {
			 ob=new("d/xuedao/obj/wulu_wan");			 
		 }else ob=new("d/xuedao/obj/wurou_wan");			 
         if (ob)
		{
			 message_vision(HBYEL+HIW"\n$N��������ʵ������������һ¯"+ob->query("name")+"�裡��\n"NOR,me); 

			 ob->set("owner",me->query("id"));
			 ob->move(me);
		}
		 me->delete_temp("lianwan_tick");
		 me->delete_temp("xd/lianwan");

		 me->add("quest/xd/lianwan/count",1);

		 me->start_busy(1);
     }
	 else {
	     message_vision(HIB"\n��Ȼһ�ɽ���ζ��������ԭ���Ƿ���һ��С�ģ����ƹ��󣬽���һ¯����ȫ�������ˡ���\n"NOR,me); 
		 message_vision(HIY"\nʧ�ܣ��㼫���ɥ��\n"NOR,me); 
  
		 me->start_busy(5);
		 me->delete_temp("lianwan_tick");
		 me->add("quest/xd/lianwan/fail",1);
		 me->set("quest/xd/lianwan/time",time());

		 me->delete_temp("xd");
   }
   this_object()->delete("lianwan");
   return 1;
}