// rebuild for smy job
// by Lklv 2002.07.12
// hehe by Ciwei 2004
// update by lsxk ,����TASKREWARD_Dͳһ���㾭�齱����  2008/1/8

#include <ansi.h>

#define JOB_NPC "/d/gb/npc/xixia-wushi"
#define JOB_PLACE "/d/xingxiu/silk3"

private void give_raward(object me);

int update_condition(object me, int duration)
{
	//object *lineup;
	object *team;
	//object *ob;
	object fbroom;
	int lvl,index,i;

	fbroom=me->query_temp("fbroom");
	
	if (me->query_temp("smyfail"))
	{
		 //���ٸ����ռ� 
		write(HIY "���������ģ�����ʧ�ܡ�\n" NOR);
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team) {
				//me->set_temp("smy_job/team",team);//��¼����           			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[index]);
				team[index]->move("/d/xingxiu/silk3");
				team[index]->delete_temp("smyfail");
			}   
			}
           else {
			   me->move("/d/xingxiu/silk3");
			   me->delete_temp("smyfail");
		   }   
           
			destruct(fbroom);
		}
		log_file( "job/smy", sprintf("%8s%-10s������Ħ�������뿪ʧ�ܣ����飺%d��",
		   me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		 me->delete_temp("smyfail");
		return 0;
		
	}
	
	//ob = all_inventory(fbroom);//��ȡ���������
	if( duration == me->query_temp("smy_job/time")){
		if(!me->query_team()){
			lvl = me->query("max_pot");
		}
		else {
			//lineup = me->query_lineup();
			
			team = me->query_team();
			me->set_temp("smy_job/team",team);//��¼����
			
			lvl = 0;
			for(index=0;index<sizeof(team);index++){
				if( team[index]->query("max_pot") > lvl )
				lvl = team[index]->query("max_pot");
			}
			
		}
		me->set_temp("smy_job/lvl", lvl-120-random(10) );
		me->set_temp("smy_job/num",sizeof( team ) ); //��¼��������
	}
		
	if( duration <= 1 && !me->query_temp("smy_job")){
		write(HIY "��ʱ���ѹ�������ʧ�ܡ�\n" NOR);
		me->add_condition("job_busy",120);
		//���ٸ����ռ� 
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team)
			{
           			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[index]);
				team[index]->move("/d/xingxiu/silk3");
			}
			}
            
            else me->move("/d/xingxiu/silk3");		

			destruct(fbroom);
		}
		log_file("job/smy", sprintf("%8s%-10s������Ħ������ʱ�䲻��ʧ�ܣ����飺%d��",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		return 0;
	}
		
	if( me->query_temp("smy_job/enter")
	 && environment(me) != fbroom) {
		 
	 	if( !present( "xixia wushi", environment(me) ) && me->query_temp("smy_job/finish") )
	 	{
			
			//�Ƚ���
		    give_raward(me);
			
	
	 		
			return 0;
	 	}
	 	
		tell_object(me,HIY "������ְ�أ�����ʧ�ܡ�\n" NOR);
	    //���ٸ����ռ� 
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team) {
				//me->set_temp("smy_job/team",team);//��¼����           			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[index]);
				team[index]->move("/d/xingxiu/silk3");
			}   
			}
           else me->move("/d/xingxiu/silk3");			

			destruct(fbroom);
		}
		log_file( "job/smy", sprintf("%8s%-10s������Ħ�������뿪ʧ�ܣ����飺%d��",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("smy_job");
		me->delete_temp("fbroom");
		me->apply_condition("smy_job",-1);
		me->apply_condition("job_busy", 120);
		return 0;
	}
	
	if(
		me->query_temp("smy_job/finish") >= 20//���³��ܹ�10�飬��ǰ��8�飬 by lsxk@hsbbs 2008/1/10
	 ///�޾���ʵ������ ���ԷŴ�9 .... and more
		&& environment(me) == me->query_temp("fbroom")){
		if( present( "xixia wushi", environment(me) ) )
		return 1;	
	  
	    give_raward(me);
	   
		
		return 0;
	}
	
	if( duration == 5
	 && environment(me) == me->query_temp("fbroom") 
	 && !me->query_temp("smy_job/enter") ){
	 	///��ʼ	 	
		me->set_temp("smy_job/enter",1);
		me->set_temp("smy_job/time",random(8));
	}
	if( duration < 5
	 && !me->query_temp("smy_job/enter") ){
		 //���ٸ����ռ� 
		if (fbroom) 
		{
			
			team = me->query_team();
           	if (team) {		
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[index]);
				team[index]->move("/d/xingxiu/silk3");
			}           
			}
			 else me->move("/d/xingxiu/silk3");
			destruct(fbroom);
		}
		tell_object(me,HIY "���ٶ�̫����������ʿ�ѹ���Ħ�£�����ʧ�ܡ�\n" NOR);
		log_file( "job/smy", sprintf("%8s%-10s������Ħ�������ٶ�̫��ʧ�ܣ����飺%d��",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("smy_job");
		me->apply_condition("smy_job",-1);
		me->apply_condition("job_busy",120);
		return 0;
	}
	/*
	ÿ���1 c ��һ�� (�ָ���7c)			
	��ҿ�������10 c 5c �����ߵ�smy
	5 c ����׼��״̬
	*/
	if(environment(me) == me->query_temp("fbroom") && me->query_temp("smy_job") ){
		object npc;
		switch (duration){
			case 9:
			case 7:
				if ( random(80) >75 )
				message_vision(CYN "һ���������εķ򸾣�Ů����ë¿�����˲��У���������ɽ�¡�\n" NOR, me);
				else if ( random(80) >50 )
				message_vision(BLU "Զ������һ��Ұ�޵Ľ�������ϸ���������·��Ǻ���\n" NOR, me);
				else
				message_vision(BLU "ɽ���µ�ɽ�ȴ���һ�������ĳ�Х������ë���Ȼ��\n" NOR, me);
				break;
			case 5:	
				message_vision(BLU "һ���Х��ɽ��ι���ɽ������ͱ��Եø�����ɭ��\n" NOR, me);
				break;			
			case 3:
				message_vision(CYN"Զ����ɽ·����һ����Х����Լ��������ʩչ�Ṧ�ɳ۶�����\n"NOR, me);
				break;
			case 1:	

              //�������ʿû��������ʧ��
                 if(present("xixia wushi", environment(me)))
	                   {
						   message_vision(CYN"$N����̫�������˵��ˣ���������ʧ���ˡ�\n"NOR, me);
						   me->set_temp("smyfail",1);
						   return 1;
					   }
			  
				message_vision(CYN"ɽ�±����С·������������Ӱ��$N���������������Ӱս����һ��\n"NOR, me);
				me->add_temp("smy_job/finish",1);
				
				npc = new(JOB_NPC);
                npc->set("targat",me);				
				npc->move(environment(me));
				
				npc = new(JOB_NPC);
				npc->set("targat",me);
				npc->move(environment(me));
				
				
				if (me->query_temp("smy_job/finish")>9)
				{
					npc = new(JOB_NPC);
				    npc->set("targat",me);
				    npc->move(environment(me));				
				}
								
				//lineup = me->query_lineup();
				team = me->query_team();
				if(team)
				{
					index=sizeof(team);
					for(index=0;index<sizeof(team);index++)
					{
						if(index<2) continue;
						npc = new(JOB_NPC);
						npc->set("targat",me);
						npc->move(environment(me));						
					}
				}
				break;
		}
	}
		
	me->apply_condition("smy_job", duration-1);
	
	if(duration==1)
	{
		me->apply_condition("smy_job", 7);
		if (wizardp(me)) 
			tell_object(me,HIR "������7��\n" NOR);
		message("wizard", HIG"������7��\n"NOR, environment(me), me);
	}
	if (wizardp(me))
		tell_object(me,HIR "���Լ�ʱ��"+duration+"��\n" NOR);
	message("wizard", HIG"���Լ�ʱ��"+duration+"��\n"NOR, environment(me), me);
	return 1;
}

private void give_raward(object me)
{
	//object* lineup;
	object *team;
	object fbroom;
	int i,j,x,y,count,finish;
		
	if(!me) return;
			
	//lineup = me->query_temp("smy_job/lineup");
	 team = me->query_temp("smy_job/team");//��ֹ����
	 //team = me->query_team();
	 fbroom = me->query_temp("fbroom");
	/*	
		if( team ){
			if( me->query_temp("smy_job/num") > sizeof( team ) )
				count = me->query_temp("smy_job/num");
			else
				count = sizeof(team);
		}
		else
			count = 1;
    */
	//if ( i == 0) i=1;	 
	
	
	j = me->query_temp("smy_job/finish");
    finish=me->query_temp("smy_job/finish");
	if (me->query("relife/times"))
	{
		x=j+random(1+j);
	}else x=random(j+1);
	
	x=(int)x/4;

	if( !team ){
       //����		
		me->apply_condition("gb_job_busy",60);
		me->delete_temp("smy_job");		
		me->clear_condition("smy_job");
		me->set("job_name", "������Ħ��");
		//write("�����ǵ��˸��������������������ģʽ���뱣������job��־����ϵwiz��\n");
		
          if(j > 1 && j <= 4 )
			  TASKREWARD_D->get_reward(me,"��Ħ��",1,1,x,0,2,j-1,200);
              //TASKREWARD_D->get_reward(me,"��Ħ��",1,1,(me->query("relife/times")?(j+random(1+j)):random(j+1)),0,3,j-1,0);
          else if(j == 1)
			 TASKREWARD_D->get_reward(me,"��Ħ��",1,1,x,0,1,1,100);
             // TASKREWARD_D->get_reward(me,"��Ħ��",1,1,(me->query("relife/times")?(j+random(1+j)):random(j+1)),0,1,1,0);
           else if(j>10 && j<20)
			  TASKREWARD_D->get_reward(me,"��Ħ��",1,1,x,0,3,j+1,1500);
		   else if(j>=20)
			  TASKREWARD_D->get_reward(me,"��Ħ��",1,1,x,0,3,j+1,3000);
             // TASKREWARD_D->get_reward(me,"��Ħ��",1,1,(me->query("relife/times")?(j+random(1+j)):random(j+1)),0,4,j,0);
		  else TASKREWARD_D->get_reward(me,"��Ħ��",1,1,x,0,3,j,500);

		  if( me->query_condition("fx_busy") > 50 )
			me->apply_condition("fx_busy",50);
		    
			
			
			
	
	   if (finish >= 5)
	 {
		 me->set("title",HIY"��Ħ�¡�ʿ��"NOR);
		 //me->set("mytitle/quest/smytitle",HIB"��Ħ�¡�ʿ��"NOR);
		 
	 }
     if (finish >= 10)
	 {
		 me->set("title",HIY"��Ħ�¡��Խ�"NOR);
		 //me->set("mytitle/quest/smytitle",HIB"��Ħ�¡��Խ�"NOR);
		
	 }
	 
	 if (finish >= 20)
	 {
		 me->set("title",HIY"��Ħ�¡���"NOR);
		 me->set("mytitle/quest/smytitle",HIB"��Ħ�¡���"NOR);
	 }

      if (environment(me) == fbroom) {				
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,me);
			    me->move("/d/xingxiu/silk3");
			}	 
	
			
		if (fbroom) 
		{			
			destruct(fbroom);
		}
	}
	else{
		//���
		//sizeof(team)
		write("��������Ӹ��������������������ģʽ,���Ƕ�Ա�޽������뱣������job��־����ϵwiz��\n");
		for(i = 0;i<sizeof(team);i++){
			if(userp(team[i])) {
				write("��Ա��Ϣ:"+team[i]->query("name")+"\n");
					team[i]->apply_condition("gb_job_busy", 30);
					team[i]->delete_temp("smy_job");
					team[i]->clear_condition("smy_job");
					team[i]->set("job_name", "������Ħ��");
					if (team[i]->query("relife/times"))
					{
						y=j+random(1+j);
					}
					else y=random(j+1);
					
					y=(int)y/4;	

                                  if(j > 1 && j <= 4 )
									  TASKREWARD_D->get_reward(team[i],"��Ħ��",1,1,y,0,2,j-1,200);
                                     //TASKREWARD_D->get_reward(lineup[i],"��Ħ��",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,3,j-1,0);
                                  else if(j == 1)
									  TASKREWARD_D->get_reward(team[i],"��Ħ��",1,1,y,0,1,1,100);
                                      //TASKREWARD_D->get_reward(lineup[i],"��Ħ��",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,1,1,0);
                                   else if(j>10 && j<20)
									   TASKREWARD_D->get_reward(team[i],"��Ħ��",1,1,y,0,3,j+1,1500);
								   else if(j>=20)
									   TASKREWARD_D->get_reward(team[i],"��Ħ��",1,1,y,0,3,j+1,3000);
								  else
									 TASKREWARD_D->get_reward(team[i],"��Ħ��",1,1,y,0,3,j,500);
                                    //  TASKREWARD_D->get_reward(lineup[i],"��Ħ��",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,4,j,0);

					if( team[i]->query_condition("fx_busy") > 50 )
						team[i]->apply_condition("fx_busy",30+random(20));
					
					
					   if (finish >= 5)
	 {
		 team[i]->set("title",HIY"��Ħ�¡�ʿ��"NOR);
		 //team[i]->set("mytitle/quest/smytitle",HIY"��Ħ�¡�ʿ��"NOR);
		 
	 }
     if (finish >= 10)
	 {
		 team[i]->set("title",HIY"��Ħ�¡��Խ�"NOR);
		 //team[i]->set("mytitle/quest/smytitle",HIY"��Ħ�¡��Խ�"NOR);
		
	 }
	 
	 if (finish >= 20)
	 {
		 team[i]->set("title",HIY"��Ħ�¡���"NOR);
		 team[i]->set("mytitle/quest/smytitle",HIY"��Ħ�¡���"NOR);
	 }
	  
					
					if (environment(team[i]) == fbroom) {				
				         message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[i]);
				         team[i]->move("/d/xingxiu/silk3");
				}					
					
				}		
				
				
			}
		
		if (fbroom) 
		{			
			destruct(fbroom);
		}
		}
    me->delete_temp("fbroom");
	me->delete_temp("smy_job");
	me->clear_condition("smy_job");//��ֹBug
}
