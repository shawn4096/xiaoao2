// rebuild for smy job
// by Lklv 2002.07.12
// hehe by Ciwei 2004
// update by lsxk ,����TASKREWARD_Dͳһ���㾭�齱����  2008/1/8
// cre by sohu@xojh 
//�ɹ�����ȫ���

#include <ansi.h>

#define JOB_NPC "/d/quanzhen/npc/menggu-wushi"
#define JOB_PLACE "/d/quanzhen/yuzhengong"
//string* weizhi,place;

private void give_raward(object me);

int update_condition(object me, int duration)
{	
    object* lineup;
	object *team;
	string place,cplace;
	object fbroom;
	int lvl,index;
	
	
	fbroom=me->query_temp("fbroom");	
	
	if (me->query_temp("mgrqfail"))
	{
		 //���ٸ����ռ� 
		write(HIY "���������ģ�����ʧ�ܡ�\n" NOR);
		if (fbroom) 
		{
			message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,me);			
			me->move("/d/quanzhen/yuzhengong");	
			destruct(fbroom);
		}
		
		log_file("job/mgrqjob", sprintf("%8s%-10s�����ɹ����������뿪ʧ�ܣ����飺%d��",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		 me->delete_temp("mgrqfail");
		 me->delete_temp("mgrq_job");
		return 0;
		
	}
	
	if( duration == me->query_temp("mgrq_job/time")){
		if(!me->query_lineup()){
			lvl = me->query("max_pot");
		}
		else {
			lineup = me->query_lineup();
			lvl = 0;
			for(index=0;index<sizeof(lineup);index++){
				if( lineup[index]->query("max_pot") > lvl )
				lvl = lineup[index]->query("max_pot");
			}
			me->set_temp("mgrq_job/lineup",lineup);
		}
		me->set_temp("mgrq_job/lvl", lvl-120-random(10) );
		me->set_temp("mgrq_job/num",sizeof( lineup ) );
	}
		
	
	
	
	if( duration <= 1 && !me->query_temp("mgrq_job")){
		write(HIY "��ʱ���ѹ�������ʧ�ܡ�\n" NOR);
		me->add_condition("job_busy",60);		
		
		//���ٸ����ռ� 
		if (fbroom) 
		{
			message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,me);			
			me->move("/d/quanzhen/yuzhengong");	
			destruct(fbroom);
		}
		
		
		log_file("job/mgrqjob", sprintf("%8s%-10s�����ɹ���������ʱ�䲻��ʧ�ܣ����飺%d��",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		return 0;
	}
	//place=me->query_temp("qz/mgrqjob/place");
	//cplace=me->query_temp("qz/mgrqjob/cplace");
	
	if( me->query_temp("mgrq_job/enter") && environment(me) != fbroom)
	{
		if( !present( "menggu wushi", environment(me) ) && me->query_temp("mgrq_job/finish") )
	 	{
			
			//�Ƚ���
		    give_raward(me);	 		
			return 0;
	 	}
		tell_object(me,HIY "������ְ�أ�����ʧ�ܡ�\n" NOR);
		//���ٸ����ռ� 
		if (fbroom) 
		{
			message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,me);			
			me->move("/d/quanzhen/yuzhengong");	
			destruct(fbroom);
		}
		log_file( "job/smy", sprintf("%8s%-10s�����ɹ����������뿪ʧ�ܣ����飺%d��",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("mgrq_job");
		me->apply_condition("mgrq_job",-1);
		me->apply_condition("job_busy", 60);
		return 0;
		
	}	
	
	
	

	if(
		me->query_temp("mgrq_job/finish") >= 9 //���³��ܹ�10�飬��ǰ��8�飬 by lsxk@hsbbs 2008/1/10
	 ///�޾���ʵ������ ���ԷŴ�9 .... and more
		&& environment(me) == me->query_temp("fbroom"))
	{
		if( present( "menggu wushi", environment(me) ) )
		return 1;
		give_raward(me);
		return 0;
	}
	
	if( duration == 5
	 && environment(me) == me->query_temp("fbroom") 
	 && !me->query_temp("mgrq_job/enter") ){
	 	///��ʼ	 	
		me->set_temp("mgrq_job/enter",1);
		me->set_temp("mgrq_job/time",random(5));
	}
	if( duration < 5
	 && !me->query_temp("mgrq_job/enter") ){
		 
		 //���ٸ����ռ� 
		if (fbroom) 
		{
			message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,me);			
			me->move("/d/quanzhen/yuzhengong");	
			destruct(fbroom);
		}	 
		 
		tell_object(me,HIY "���ٶ�̫�����ɹ���ʿ�ѹ��ɹ����֣�����ʧ�ܡ�\n" NOR);
		log_file( "job/mgrqjob", sprintf("%8s%-10s�����ɹ����������ٶ�̫��ʧ�ܣ����飺%d��",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("mgrq_job");
		me->apply_condition("mgrq_job",-1);
		me->apply_condition("job_busy",60);
		return 0;
	}
	/*
	ÿ���1 c ��һ�� (�ָ���7c)			
	��ҿ�������10 c 5c �����ߵ�smy
	5 c ����׼��״̬
	*/
	if( environment(me) == me->query_temp("fbroom") && me->query_temp("mgrq_job") ){
		object npc;
		switch (duration){
			case 9:
			case 7:
				if ( random(80) >75 )
				message_vision(CYN "�����ɹ���ʿ����������ɽ�����˹�����\n" NOR, me);
				else if ( random(80) >50 )
				message_vision(BLU "Զ������һ��Ұ�޵Ľ�������ϸ���������·��Ǻ���\n" NOR, me);
				else
				message_vision(BLU + "ɽ�µ�ɽ�ȴ���һ�������ĳ�Х������ë���Ȼ��\n" NOR, me);
				break;
			case 5:	
				message_vision(BLU "һ���Х��ɽ��ι���ɽ��������ͱ��Եø�����ɭ��\n" NOR, me);
				break;			
			case 3:
				message_vision(CYN"Զ����ɽ���·�����һ����Х����Լ��������ʩչ�Ṧ�ɳ۶�����\n"NOR, me);
				break;
			case 1:	


                 if(present("menggu wushi", environment(me)))
	                   {
						   message_vision(CYN"$N����̫�������˵��ˣ���������ʧ���ˡ�\n"NOR, me);
						   me->set_temp("mgrqfail",1);
						   return 1;
					   }
					   
				message_vision(CYN"�·���С·������������Ӱ��$N���������������Ӱս����һ��\n"NOR, me);
				me->add_temp("mgrq_job/finish",1);
				
				npc = new(JOB_NPC);
                npc->set("targat",me);					
				npc->move(environment(me));
				
				npc = new(JOB_NPC);
				npc->set("targat",me);	
				npc->move(environment(me));
								
				lineup = me->query_lineup();
				if(lineup)
				{
					index=sizeof(lineup);
					for(index=0;index<sizeof(lineup);index++)
					{
						if(index<2) continue;
						npc = new(JOB_NPC);
						npc->move(environment(me));						
					}
				}
				break;
		}
	}
		
	me->apply_condition("mgrq_job", duration-1);
	
	if(duration==1)
	{
		me->apply_condition("mgrq_job", 7);
		if (wizardp(me)) 
			tell_object(me,HIR "������5��\n" NOR);
		message("wizard", HIG"������5��\n"NOR, environment(me), me);
	}
	if (wizardp(me))
		tell_object(me,HIR "���Լ�ʱ��"+duration+"��\n" NOR);
	message("wizard", HIG"���Լ�ʱ��"+duration+"��\n"NOR, environment(me), me);
	return 1;
}



private void give_raward(object me)
{
	object* lineup;
	int i,j,x,y;
	int jobs;
	object fbroom;
	if(!me) return;
			
			
	fbroom = me->query_temp("fbroom");
	i=1;	
	j = me->query_temp("mgrq_job/finish");  
	
	x=random(j+1);
	
	x=(int)x/4;
		
		me->apply_condition("mgrq_job_busy",60);
		me->delete_temp("mgrq_job");
		me->clear_condition("mgrq_job");
		me->set("job_name", "�����ɹ�����");
		
          if(j ==1)
			 // TASKREWARD_D->get_reward(me,"�ɹ�����",1,1,x,0,1,1,0); 
             TASKREWARD_D->get_reward(me,"�ɹ�����",1,0,0,2,0,0,100); 		 
          else 
			 TASKREWARD_D->get_reward(me,"�ɹ�����",1,0,0,j+12,0,0,300);	
	   jobs=me->query("job_time/�ɹ�����");
	   if (random(jobs)>8000
			&& random(me->query("kar"))>27			
			&& !me->query("quest/qz/xtg/wuqi/start")
			&& (jobs % 50) ==0	
			&& me->query("quest/qz/dichuan"))
		{
			
				message_vision(HIC"�´�ͨ��Զ����$N�����˴�Ĵָ��˵���������������Ϊ�Ҵ�ȫ�湤�������ǲ�����\n"NOR,me);
				tell_object(me,me->query("name")+"���㲻æʱ�������������ҿ������޲���\n");
				message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ���ú´�ͨ����㣡\n"NOR, users());
				//message("channel:chat", HIC"�����졿�´�ͨ��"+me->query("name")+"������ȫ����ĵ��ӣ��뽭��ͬ������ˡ���\n"NOR, users());
			
				me->set("quest/qz/xtg/wuqi/start",1);
		}
		
		if (environment(me) == fbroom) {				
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,me);
			    me->move("/d/quanzhen/yuzhengong");
			}	 
			
		if (fbroom) 
		{			
			destruct(fbroom);
		}
		
		me->add("party/gongji",2+random(4));
		me->delete_temp("fbroom");
		me->delete_temp("mgrq_job");
		me->clear_condition("mgrq_job_busy");
		me->clear_condition("mgrq_job");//��ֹBug
}
