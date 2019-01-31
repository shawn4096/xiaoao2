// rebuild for smy job
// by Lklv 2002.07.12
// hehe by Ciwei 2004
// update by lsxk ,调用TASKREWARD_D统一计算经验奖励。  2008/1/8

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
		 //销毁副本空间 
		write(HIY "你力不从心，任务失败。\n" NOR);
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team) {
				//me->set_temp("smy_job/team",team);//记录队伍           			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
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
		log_file( "job/smy", sprintf("%8s%-10s抗敌颂摩崖任务，离开失败，经验：%d。",
		   me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		 me->delete_temp("smyfail");
		return 0;
		
	}
	
	//ob = all_inventory(fbroom);//获取副本内物件
	if( duration == me->query_temp("smy_job/time")){
		if(!me->query_team()){
			lvl = me->query("max_pot");
		}
		else {
			//lineup = me->query_lineup();
			
			team = me->query_team();
			me->set_temp("smy_job/team",team);//记录队伍
			
			lvl = 0;
			for(index=0;index<sizeof(team);index++){
				if( team[index]->query("max_pot") > lvl )
				lvl = team[index]->query("max_pot");
			}
			
		}
		me->set_temp("smy_job/lvl", lvl-120-random(10) );
		me->set_temp("smy_job/num",sizeof( team ) ); //记录队伍人数
	}
		
	if( duration <= 1 && !me->query_temp("smy_job")){
		write(HIY "你时间已过，任务失败。\n" NOR);
		me->add_condition("job_busy",120);
		//销毁副本空间 
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team)
			{
           			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
				team[index]->move("/d/xingxiu/silk3");
			}
			}
            
            else me->move("/d/xingxiu/silk3");		

			destruct(fbroom);
		}
		log_file("job/smy", sprintf("%8s%-10s抗敌颂摩崖任务，时间不够失败，经验：%d。",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		return 0;
	}
		
	if( me->query_temp("smy_job/enter")
	 && environment(me) != fbroom) {
		 
	 	if( !present( "xixia wushi", environment(me) ) && me->query_temp("smy_job/finish") )
	 	{
			
			//先奖励
		    give_raward(me);
			
	
	 		
			return 0;
	 	}
	 	
		tell_object(me,HIY "你擅离职守，任务失败。\n" NOR);
	    //销毁副本空间 
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team) {
				//me->set_temp("smy_job/team",team);//记录队伍           			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
				team[index]->move("/d/xingxiu/silk3");
			}   
			}
           else me->move("/d/xingxiu/silk3");			

			destruct(fbroom);
		}
		log_file( "job/smy", sprintf("%8s%-10s抗敌颂摩崖任务，离开失败，经验：%d。",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("smy_job");
		me->delete_temp("fbroom");
		me->apply_condition("smy_job",-1);
		me->apply_condition("job_busy", 120);
		return 0;
	}
	
	if(
		me->query_temp("smy_job/finish") >= 20//更新成总共10组，以前是8组， by lsxk@hsbbs 2008/1/10
	 ///无具体实际限制 可以放大到9 .... and more
		&& environment(me) == me->query_temp("fbroom")){
		if( present( "xixia wushi", environment(me) ) )
		return 1;	
	  
	    give_raward(me);
	   
		
		return 0;
	}
	
	if( duration == 5
	 && environment(me) == me->query_temp("fbroom") 
	 && !me->query_temp("smy_job/enter") ){
	 	///开始	 	
		me->set_temp("smy_job/enter",1);
		me->set_temp("smy_job/time",random(8));
	}
	if( duration < 5
	 && !me->query_temp("smy_job/enter") ){
		 //销毁副本空间 
		if (fbroom) 
		{
			
			team = me->query_team();
           	if (team) {		
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
				team[index]->move("/d/xingxiu/silk3");
			}           
			}
			 else me->move("/d/xingxiu/silk3");
			destruct(fbroom);
		}
		tell_object(me,HIY "你速度太慢，西夏武士已过颂摩崖，任务失败。\n" NOR);
		log_file( "job/smy", sprintf("%8s%-10s抗敌颂摩崖任务，速度太慢失败，经验：%d。",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("smy_job");
		me->apply_condition("smy_job",-1);
		me->apply_condition("job_busy",120);
		return 0;
	}
	/*
	每间隔1 c 来一批 (恢复到7c)			
	玩家可以设置10 c 5c 用于走到smy
	5 c 进入准备状态
	*/
	if(environment(me) == me->query_temp("fbroom") && me->query_temp("smy_job") ){
		object npc;
		switch (duration){
			case 9:
			case 7:
				if ( random(80) >75 )
				message_vision(CYN "一对契丹服饰的夫妇，女的骑毛驴，男人步行，缓缓经过山崖。\n" NOR, me);
				else if ( random(80) >50 )
				message_vision(BLU "远处传来一阵野兽的叫声，仔细听起来，仿佛狼嚎。\n" NOR, me);
				else
				message_vision(BLU "山崖下的山谷传来一声凄厉的长啸，令人毛骨悚然。\n" NOR, me);
				break;
			case 5:	
				message_vision(BLU "一阵呼啸的山风刮过，山两侧的峭壁显得格外阴森。\n" NOR, me);
				break;			
			case 3:
				message_vision(CYN"远处的山路传来一阵轻啸，隐约听得有人施展轻功飞驰而来。\n"NOR, me);
				break;
			case 1:	

              //如果有武士没死，就算失败
                 if(present("xixia wushi", environment(me)))
	                   {
						   message_vision(CYN"$N动作太慢惊动了敌人，导致任务失败了。\n"NOR, me);
						   me->set_temp("smyfail",1);
						   return 1;
					   }
			  
				message_vision(CYN"山崖北面的小路上闪出几条人影，$N纵身而起，立即和人影战在了一起。\n"NOR, me);
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
			tell_object(me,HIR "重新置7。\n" NOR);
		message("wizard", HIG"重新置7。\n"NOR, environment(me), me);
	}
	if (wizardp(me))
		tell_object(me,HIR "调试计时："+duration+"。\n" NOR);
	message("wizard", HIG"调试计时："+duration+"。\n"NOR, environment(me), me);
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
	 team = me->query_temp("smy_job/team");//防止作弊
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
       //单人		
		me->apply_condition("gb_job_busy",60);
		me->delete_temp("smy_job");		
		me->clear_condition("smy_job");
		me->set("job_name", "抗敌颂摩崖");
		//write("现在是单人副本任务奖励，若你是组队模式，请保存完整job日志并联系wiz。\n");
		
          if(j > 1 && j <= 4 )
			  TASKREWARD_D->get_reward(me,"颂摩崖",1,1,x,0,2,j-1,200);
              //TASKREWARD_D->get_reward(me,"颂摩崖",1,1,(me->query("relife/times")?(j+random(1+j)):random(j+1)),0,3,j-1,0);
          else if(j == 1)
			 TASKREWARD_D->get_reward(me,"颂摩崖",1,1,x,0,1,1,100);
             // TASKREWARD_D->get_reward(me,"颂摩崖",1,1,(me->query("relife/times")?(j+random(1+j)):random(j+1)),0,1,1,0);
           else if(j>10 && j<20)
			  TASKREWARD_D->get_reward(me,"颂摩崖",1,1,x,0,3,j+1,1500);
		   else if(j>=20)
			  TASKREWARD_D->get_reward(me,"颂摩崖",1,1,x,0,3,j+1,3000);
             // TASKREWARD_D->get_reward(me,"颂摩崖",1,1,(me->query("relife/times")?(j+random(1+j)):random(j+1)),0,4,j,0);
		  else TASKREWARD_D->get_reward(me,"颂摩崖",1,1,x,0,3,j,500);

		  if( me->query_condition("fx_busy") > 50 )
			me->apply_condition("fx_busy",50);
		    
			
			
			
	
	   if (finish >= 5)
	 {
		 me->set("title",HIY"颂摩崖·士卒"NOR);
		 //me->set("mytitle/quest/smytitle",HIB"颂摩崖·士卒"NOR);
		 
	 }
     if (finish >= 10)
	 {
		 me->set("title",HIY"颂摩崖·裨将"NOR);
		 //me->set("mytitle/quest/smytitle",HIB"颂摩崖·裨将"NOR);
		
	 }
	 
	 if (finish >= 20)
	 {
		 me->set("title",HIY"颂摩崖·大将"NOR);
		 me->set("mytitle/quest/smytitle",HIB"颂摩崖·大将"NOR);
	 }

      if (environment(me) == fbroom) {				
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,me);
			    me->move("/d/xingxiu/silk3");
			}	 
	
			
		if (fbroom) 
		{			
			destruct(fbroom);
		}
	}
	else{
		//组队
		//sizeof(team)
		write("现在是组队副本任务奖励，若你是组队模式,但是队员无奖励，请保存完整job日志并联系wiz。\n");
		for(i = 0;i<sizeof(team);i++){
			if(userp(team[i])) {
				write("队员信息:"+team[i]->query("name")+"\n");
					team[i]->apply_condition("gb_job_busy", 30);
					team[i]->delete_temp("smy_job");
					team[i]->clear_condition("smy_job");
					team[i]->set("job_name", "抗敌颂摩崖");
					if (team[i]->query("relife/times"))
					{
						y=j+random(1+j);
					}
					else y=random(j+1);
					
					y=(int)y/4;	

                                  if(j > 1 && j <= 4 )
									  TASKREWARD_D->get_reward(team[i],"颂摩崖",1,1,y,0,2,j-1,200);
                                     //TASKREWARD_D->get_reward(lineup[i],"颂摩崖",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,3,j-1,0);
                                  else if(j == 1)
									  TASKREWARD_D->get_reward(team[i],"颂摩崖",1,1,y,0,1,1,100);
                                      //TASKREWARD_D->get_reward(lineup[i],"颂摩崖",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,1,1,0);
                                   else if(j>10 && j<20)
									   TASKREWARD_D->get_reward(team[i],"颂摩崖",1,1,y,0,3,j+1,1500);
								   else if(j>=20)
									   TASKREWARD_D->get_reward(team[i],"颂摩崖",1,1,y,0,3,j+1,3000);
								  else
									 TASKREWARD_D->get_reward(team[i],"颂摩崖",1,1,y,0,3,j,500);
                                    //  TASKREWARD_D->get_reward(lineup[i],"颂摩崖",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,4,j,0);

					if( team[i]->query_condition("fx_busy") > 50 )
						team[i]->apply_condition("fx_busy",30+random(20));
					
					
					   if (finish >= 5)
	 {
		 team[i]->set("title",HIY"颂摩崖·士卒"NOR);
		 //team[i]->set("mytitle/quest/smytitle",HIY"颂摩崖·士卒"NOR);
		 
	 }
     if (finish >= 10)
	 {
		 team[i]->set("title",HIY"颂摩崖·裨将"NOR);
		 //team[i]->set("mytitle/quest/smytitle",HIY"颂摩崖·裨将"NOR);
		
	 }
	 
	 if (finish >= 20)
	 {
		 team[i]->set("title",HIY"颂摩崖·大将"NOR);
		 team[i]->set("mytitle/quest/smytitle",HIY"颂摩崖·大将"NOR);
	 }
	  
					
					if (environment(team[i]) == fbroom) {				
				         message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[i]);
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
	me->clear_condition("smy_job");//防止Bug
}
