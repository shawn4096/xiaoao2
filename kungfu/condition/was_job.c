// rebuild for was job
// by renlai

#include <ansi.h>

#define JOB_NPC "/d/was/npc/menggu-wushi"
#define JOB_PLACE "/d/was/was"


private void give_raward(object me);

int update_condition(object me, int duration)
{
	//object *lineup;
	object *team;
	object *ob;
	//object *ob;
	object fbroom;
	string party;
	string npcname;
	int lvl,index,i,j,guan;

	fbroom=me->query_temp("fbroom");
	
	ob = all_inventory(environment(me));
	
	//��ֹ�ڸ���������������
	if (me->query_temp("was_job/team"))
	{
	    if (me->query_temp("was_job/team") !=me->query_team())	
	    {
		    write(HIY "����ӳ������⣬����ʧ�ܡ�\n" NOR);
		    me->set_temp("wasfail",1);
	    }
	}
	
	if (me->query_temp("wasfail"))
	{
		 //���ٸ����ռ� 
		write(HIY "���������ģ�����ʧ�ܡ�\n" NOR);
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team) {
				CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")һ�д����½������ʧ�ܣ�\n"NOR);
				       			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[index]);
				if (living(team[index])) team[index]->move(JOB_PLACE);	
				team[index]->delete_temp("wasfail");
				team[index]->delete_temp("was_job");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("was_busy",70);	
			}   
			}
           else {
			   CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")�����½������ʧ�ܣ�\n"NOR);	
			   if (living(me))  me->move(JOB_PLACE);
			   me->delete_temp("wasfail");
			   me->delete_temp("was_job");
		   }   
           
			destruct(fbroom);
		}
		log_file( "job/was", sprintf("%8s%-10s�´�����������Ա���������뿪����ʧ�ܣ����飺%d��",
		   me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		 me->delete_temp("wasfail");
		 me->delete_temp("was_job");
		 me->apply_condition("job_busy",10);
		 me->apply_condition("was_busy",70);		
		return 0;
		
	}
	
	
	//�жϳ�ʱ���ڸ���������ʧ��
	
	if(duration==100)
	{
		write(HIY "����ʱ̫�ã�����ʧ�ܡ�\n" NOR);
		me->set_temp("wasfail",1);
	}
	
	if( duration >= 5
	 && environment(me) == fbroom 
	 && !me->query_temp("was_job/enter") ){
	 	///��ʼ	 	
		me->set_temp("was_job/enter",1);
		me->set_temp("was_job/time",random(8));
	}
	
	
	if( duration == me->query_temp("was_job/time")){
		if(!me->query_team()){
			lvl = me->query("max_pot");
		}
		else {
			//lineup = me->query_lineup();
			
			team = me->query_team();
			me->set_temp("was_job/team",team);//��¼����
			
			lvl = 0;
			for(index=0;index<sizeof(team);index++){
				if( team[index]->query("max_pot") > lvl )
				lvl = team[index]->query("max_pot");
			}
			
		}
		me->set_temp("was_job/lvl", lvl-120-random(10) );
		me->set_temp("was_job/num",sizeof( team ) ); //��¼��������
	}
	
	//ʱ�䵽�ˣ�����û�������¸���
	if( duration < 5
	 && !me->query_temp("was_job/enter") ){
		 //���ٸ����ռ� 
		if (fbroom) 
		{
			
			team = me->query_team();
           	if (team) {		
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[index]);
				team[index]->move("/d/was/was");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("was_busy",70);	
			}           
			}
			 else me->move("/d/was/was");
			destruct(fbroom);
		}
		tell_object(me,HIY "��ϵ�����Ϊʱ��������Ⱥ���Ѿ�����������ʧ�ܡ�\n" NOR);
		log_file( "job/was", sprintf("%8s%-10s�´����������ٶ�̫��ʧ�ܣ����飺%d��",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("was_job");
		me->apply_condition("was_job",-1);
		me->apply_condition("job_busy",10);
		me->apply_condition("was_busy",70);	
		return 0;
	}		
	
	//&& !me->query_temp("was_job")
	//ս��ʱ��̫��
	if( duration <= 1){
		write(HIY "����ʱ̫�ã���ݾ��ߵ�������ʧ�ܡ�\n" NOR);
		
		//���ٸ����ռ� 
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team)
			{
           			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[index]);
				team[index]->move("/d/was/was");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("was_busy",70);	
			}
			}
            
			 destruct(fbroom);
		}
		else {
			me->apply_condition("job_busy",10);
		    me->apply_condition("was_busy",70);	
			me->move("/d/was/was");
		}
		log_file("job/was", sprintf("%8s%-10s�´���������ʱ�䲻��ʧ�ܣ����飺%d��",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		return 0;
	}
	
	
	
	if( me->query_temp("was_job/enter") && environment(me) != fbroom) {
		 
	 	if( !present( "menggu wushi", environment(me)) && me->query_temp("was_job/finish") )
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
						
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[index]);
				team[index]->move("/d/was/was");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("was_busy",70);
			}   
			}
           else me->move("/d/was/was");			

			destruct(fbroom);
		}
		log_file( "job/was", sprintf("%8s%-10s�´����������뿪ʧ�ܣ����飺%d��",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("was_job");
		me->delete_temp("fbroom");
		me->apply_condition("was_job",-1);
		me->apply_condition("job_busy",10);
		me->apply_condition("was_busy",70);	
		return 0;
	}
	
	if(
		me->query_temp("was_job/finish") >= 1000//���³�1000�� by renlai
	 ///�޾���ʵ������ ���ԷŴ�9 .... and more
		&& environment(me) == me->query_temp("fbroom")){
		if( present( "menggu wushi", environment(me) ) )
		return 1;	
	  
	    give_raward(me);
	   
		
		return 0;
	}
	
	
	
	/*
	ÿ���1 c ��һ�� (�ָ���5c)				
	5 c ����׼��״̬
	*/
	if(environment(me) == fbroom && me->query_temp("was_job") ){
		object npc;	 
				 
		fbroom=environment(me);		
		switch (duration){	
		    case 10:				
				message_vision(CYN "�������ľ���֣������������������õƻ���˸֮��һ��������ƮȻ������\n" NOR, me);
                 break;		
            case 7:				
				message_vision(CYN "������һ·Ǳ�У������ܿ�Ѳ����ʿ��������ȥ������֮��ŷ�������Զ��ֹʮ���㣬����ռ��ƺ�����Ǭ����\n" NOR, me);
                 break;				
			case 6:				
				message_vision(CYN "���ϲ�ʱƮ��������ײ��ȭ�Ż���֮�����ƺ��������ڴ򶷡�\n" NOR, me);
                 break;				
			case 5:
				message_vision(BLU "�ֲ�ʱ�����ҽУ���֪�Ƿ�Ϊ���ڱ���Ѻ������Ⱥ����������\n" NOR, me);
				break;
			case 3:	
				message_vision(BLU "�����������ڵĵ�"+CHINESE_D->chinese_number(me->query_temp("was_job/finish")+1)+"��,�Ĵ�������Ҫ�ҳ�Ⱥ������λ�á�\n" NOR, me);	
				 if ((random(me->query_temp("was_job/finish"))>12) && !me->query_temp("was_quest/save") && me->query("kar")>20 && !QUEST_D->queryquest(me,"was/save"))
				 {				
                      party= me->query("family/family_name");
					  npcname="����֮��";
					  
					  switch (party)
					  {
						  case "������": npcname="������" ; break;
                	      case "������": npcname="���Ŵ�ʦ"; break;                	
                	      case "�䵱��": npcname="��Զ��"; break;
                	      case "��ɽ��": npcname="������"; break;
						  case "������": npcname="��̫��"; break;  
                          case "����": npcname="��ά��"; break;						  
					  }
					  me->set_temp("was_quest/save",npcname);//���˱��
					  message_vision(BLU "��Ȼ���ַ��ھ���һ��,��ϸһ��ȴ����"+npcname+"��$N��æ������������������ȥ������ȥ�����ˡ���\n" NOR, me);	
				 }
					  

					
                 //��ɨ����
				for( i=0; i < sizeof(ob); i++ )
	               {
                       // || 					   
		               if (ob[i]->is_corpse() ||!ob[i]->is_character()) {
					       destruct(ob[i]);					      
				         }
     			   }
                fbroom->set("short", HIM"��"+CHINESE_D->chinese_number(me->query_temp("was_job/finish")+1)+"����-����"NOR);
				break;						
			case 2:					
				message_vision(RED" ͻȻ֮�䣬�����������⣬������ִ��ѻ����ƶ�����Ѵ���������һ·������������㡣\n"NOR, me);
				
 				 me->add_temp("was_job/finish",1);				 
		        //guan= me->query_temp("was_job/finish");
				npc = new(JOB_NPC);
                npc->set("targat",me);				
				npc->move(environment(me));
				
				npc = new(JOB_NPC);
				npc->set("targat",me);
				npc->move(environment(me));
				
				
				me->delete_temp("was_up");//������¥
				
				if (me->query_temp("was_job/finish")>10)
				{
					npc = new(JOB_NPC);
				    npc->set("targat",me);
				    npc->move(environment(me));				
				}
				
				if (me->query_temp("was_job/finish")>40)
				{
					npc = new(JOB_NPC);
				    npc->set("targat",me);
				    npc->move(environment(me));				
				}
				if (me->query_temp("was_job/finish")>60)
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
		
	me->apply_condition("was_job", duration-1);
	
	if(duration==2)
	{
		me->apply_condition("was_job", 900);
		if (wizardp(me)) 
			tell_object(me,HIR "������900��\n" NOR);
		message("wizard", HIG"������900��\n"NOR, environment(me), me);
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
	int i,j,k,x,y,count,finish;
	mapping *notes;
	mapping note;
	string file;
	string party;
	string npcname;
	int wasscore;
		
	if(!me) return;
			
	
	 team = me->query_temp("was_job/team");//��ֹ����
	 //team = me->query_team();
	 fbroom = me->query_temp("fbroom");
		
	j = me->query_temp("was_job/finish");
    finish=me->query_temp("was_job/finish");
	if (me->query("relife/times"))
	{
		x=j+random(1+j);
	}else x=random(j+1);
	
	x=(int)x/4;
	
   //������߼�¼
    if (finish>me->query("was_job/level")) me->set("was_job/level",finish);    

    note=allocate_mapping(4);
    note["player"]=	me->name(1)+"("+capitalize(getuid(me))+")";
	note["playerid"]=capitalize(getuid(me));
	note["waslevel"]=finish;
	note["wasexp"]=me->query("combat_exp");

	if (file_size("/log/wastop") > 0) 
	{	
	   file = read_file("/log/wastop");	
	   notes=restore_variable(file);
	}
 
   if ( !pointerp(notes) || !sizeof(notes))
	{
		 notes = ({ note });
		 CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "������"+CHINESE_D->chinese_number(finish)+"��ɹ�����Ϊ���´��ؼ�¼�����ߣ�\n"NOR);
		 me->set_temp("title", MAG"����"+HIC"ͷ�ſ�����"NOR);
	}
    else
	{
		for(k = 0;k<sizeof(notes);k++) {
			if (finish>notes[k]["waslevel"]) {
				
				notes[k]["waslevel"]=finish; 
                notes[k]["wasexp"]=me->query("combat_exp");
               	me->set_temp("title", MAG"����"+HIC"ͷ�ſ�����"NOR);		
				
			 if (notes[k]["playerid"]==capitalize(getuid(me)))
				 CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "������"+CHINESE_D->chinese_number(finish)+"��ɹ���ˢ�����Լ��ļ�¼��Ϊ���´��ؼ�¼�����ߣ�\n"NOR);
				 else
				 {					 
					 CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "������"+CHINESE_D->chinese_number(finish)+"��ɹ���������"+ notes[k]["player"] + "��Ϊ���´��ؼ�¼�����ߣ�\n"NOR);
					 
					 notes[k]["playerid"]=capitalize(getuid(me));
                     notes[k]["player"]=me->name(1)+"("+capitalize(getuid(me))+")";	
				 }
				 				
                break;				
			}			
		}
	}	
	
	write_file("/log/wastop",save_variable(notes),1);
	
	  if (finish>=1000) {
		  //����1000��ģ���û�о���Ҳ����ν�ˡ�grin
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "������"+CHINESE_D->chinese_number(finish)+"��ɹ������������澭�ϲ�һ����\n"NOR);
		  me->set("quest/jiuyin1/pass",1);
		  QUEST_D->setmytitle(me,"jiuyintitle",HIR"������"NOR"��"HIC"�����澭����"NOR);
	  }
	  
	
	  
	 if (finish>=50)
	 {
		 int type = random(2)+1;
		 object kuangshi;
		 switch(type){
				case 1:kuangshi = new("/d/zhiye/obj/kuangshi");break;
				case 2:kuangshi = new("/d/zhiye/obj/buliao");break;
				default:break;
				}
		if(kuangshi){
			kuangshi->set_level(10);
			kuangshi->set("owner",getuid(me));
			kuangshi->move(me);
			tell_object(me,"�����������������޼�ӭ��������͵͵�ݸ���һ�����\n");
		}		 
	 }
	  
	  
		 
	 me->delete_temp("was_up");//������¥
	if( !team ){
       //����		
		me->apply_condition("job_busy",10);
		me->apply_condition("was_busy",60);
		me->delete_temp("was_job");		
		me->clear_condition("was_job");
		me->set("job_name", "�´�����");
		//write("�����ǵ��˸��������������������ģʽ���뱣������job��־����ϵwiz��\n");
		//x��ͨ�� Ŀǰ��Ч
          if(j > 1 && j <= 10 )
			  TASKREWARD_D->get_reward(me,"�´�����",2,1,x,0,1,j-1,500);             
          else if(j == 1)
			 TASKREWARD_D->get_reward(me,"�´�����",2,1,x,0,1,1,160);             
          else if(j>20 && j<=30)
			  TASKREWARD_D->get_reward(me,"�´�����",2,1,x,0,3,j,4000);
		  else if(j>30 && j<=40) 
			 TASKREWARD_D->get_reward(me,"�´�����",2,1,x,0,4,j+1,6000);
		  else if(j>40 && j<=50) 
			TASKREWARD_D->get_reward(me,"�´�����",2,1,x,0,5,j+1,8000);
		  else if(j>50) 
			TASKREWARD_D->get_reward(me,"�´�����",2,1,x,0,5,j+1,10000);            
		  else TASKREWARD_D->get_reward(me,"�´�����",2,1,x,0,2,j,800);
		  

		  if( me->query_condition("fx_busy") > 50 )
			me->apply_condition("fx_busy",50);
		 
		 //����was����
		 wasscore=0;
            if (finish>10 && finish<=20)
			{
			    wasscore=1;	
			}
			else if (finish>20)
			{
				wasscore=finish;;
			}
			
			
		 if (finish>10) {		   
			me->add("was_job/wasscore",wasscore);
			tell_object(me,HIY "��Ϊ�����³ɹ���������"+CHINESE_D->chinese_number(wasscore)+"�����»��֡�\n" NOR);
		 }		
	

      if (environment(me) == fbroom) {				
				message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,me);
			    me->move("/d/was/was");
			}	 
	
			
		if (fbroom) 
		{			
			destruct(fbroom);
		}
	}
	else{
		//���
		//sizeof(team)
		//write("��������Ӹ��������������������ģʽ,���Ƕ�Ա�޽������뱣������job��־����ϵwiz��\n");
				
		   wasscore=0;
            if (finish>10 && finish<=20)
			{
			    wasscore=1;	
			}
			else if (finish>20)
			{
				wasscore=finish;
			}
					 		
		
		for(i = 0;i<sizeof(team);i++){
			if(objectp(team[i]) && userp(team[i])) {
				write("��Ա��Ϣ:"+team[i]->query("name")+"\n");
					team[i]->apply_condition("job_busy", 10);
					team[i]->apply_condition("was_busy",60);
					team[i]->delete_temp("was_job");
					team[i]->clear_condition("was_job");
					team[i]->set("job_name", "�´�����");
					if (team[i]->query("relife/times"))
					{
						y=j+random(1+j);
					}
					else y=random(j+1);
					
					y=(int)y/4;	

                                  if(j > 1 && j <= 10 )
									  TASKREWARD_D->get_reward(team[i],"�´�����",2,1,y,0,1,j-1,500);
                                     
                                  else if(j == 1)
									  TASKREWARD_D->get_reward(team[i],"�´�����",2,1,y,0,1,1,160);
                                   else if(j>20 && j<=30) 
									   TASKREWARD_D->get_reward(team[i],"�´�����",2,1,y,0,3,j+1,4000);
								   else if(j>30 && j<=40) 
									   TASKREWARD_D->get_reward(team[i],"�´�����",2,1,y,0,4,j+1,6000);
								   else if(j>40 && j<=50) 
									   TASKREWARD_D->get_reward(team[i],"�´�����",2,1,y,0,5,j+1,8000);
								   else if(j>50) 
									   TASKREWARD_D->get_reward(team[i],"�´�����",2,1,y,0,5,j+1,10000);
                                  else
									 TASKREWARD_D->get_reward(team[i],"�´�����",2,1,y,0,2,j,1000);
                                    

					if( team[i]->query_condition("fx_busy") > 50 )
						team[i]->apply_condition("fx_busy",30+random(20));
					
	
					if (environment(team[i]) == fbroom) {				
				         message_vision(HIY"һ��������ת��$Nһ���㱣��ŷ����Լ��˳��˸����ռ䡣\n"NOR,team[i]);
				         team[i]->move("/d/was/was");
				}					
					
				}
				if (finish>10) {
				team[i]->add("was_job/wasscore",wasscore);
				tell_object(team[i],HIY "��Ϊ�����³ɹ���������"+CHINESE_D->chinese_number(wasscore)+"�����»��֡�\n" NOR);
			    
				}
				
			}		
		if (fbroom) 
		{			
			destruct(fbroom);
		}
		}
		
		
		  
	  	//�����quest�ж�
	//20�����ϲ��л���
	//����ӽ����󣬷���job��������
	
	if (finish>19 && me->query("quest/����������/��ɽ֮��/over") && !me->query("quest/����������/was/pass") && random(finish)>20) 
	{
		CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "�����³ɹ������ȳ����ɸ��֣�\n"NOR);
		message_vision(CYN "��ʱ���ء���ἡ���ɽ���䵱���ɸ������ѷ�ӵ������ֻ�����ɿ��š�������λ��ɮ��ʧǰ���緶��������ʮ��$N��л������Զ�š������۵��໥ǫ��һ����ʼ�Ⱥ���š�\n" NOR, me);
        message_vision(CYN "$N��Ԯ���ɸ����������������Ѻľ�����ʱ����·Ҳ�߲����ˡ�\n$NĬ���ڹ����������������\n" NOR, me);
		me->set("quest/����������/jiuyangzhenjing/combat_exp",me->query("combat_exp"));
	    if(QUEST_D->job_questing(me,4,"����������/was","�´�����",5000,"������",-1,""))
	      {
			  CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "��Ӫ�����ɳɹ������õ����޼ɵ�������\n"NOR);
			  message_vision(CYN "��Ȼ��$N���ߴ���������ȴ�����޼��ô������ط�ʽ��֪$Nһ�����ܡ�\n" NOR, me);
              QUEST_D->setmytitle(me,"wastitle",HIY"������Ե��"NOR);					  
	      }  
	}
	
	 else if (me->query_temp("was_quest/save"))
	{
		//CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "�����³ɹ������Ҿȵ�"+me->query_temp("was_quest/save")+"��\n"NOR);
	    if (QUEST_D->job_questing(me,3,"was/save","�´�����",1000,"������",-1,""))
		{
			QUEST_D->setmytitle(me,"wastitle",HIY"���´�Ӣ��"NOR);
			CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "��Ӫ�����ɳɹ������õ�"+me->query_temp("was_quest/save")+"������\n"NOR);
			 message_vision(CYN "����"+me->query_temp("was_quest/save")+"��$N����һ�ԣ���$N����˵��ʲô��$N�ƺ��˷ܲ��ѡ�\n" NOR, me);
		}
		else CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "Ӫ�����ɳɹ�����ϧ��Եδ����δ��"+me->query_temp("was_quest/save")+"������\n"NOR);
        me->delete_temp("was_quest/save");		
	}	
	
	else if (finish<15) CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "��̽���»�ȡ����һЩ�鱨��\n"NOR);	
    else
        CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")" + "�����³ɹ�����ϧ��δ�ȵ����ɸ��֣�ʧȥ��һ�λ�Ե��\n"NOR);
		
    me->delete_temp("fbroom");
	me->delete_temp("was_job");
	me->clear_condition("was_job");//��ֹBug
}
