// rebuild for smy job
// by Lklv 2002.07.12
// hehe by Ciwei 2004
// update by lsxk ,调用TASKREWARD_D统一计算经验奖励。  2008/1/8
// cre by sohu@xojh 
//蒙古入侵全真教

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
		 //销毁副本空间 
		write(HIY "你力不从心，任务失败。\n" NOR);
		if (fbroom) 
		{
			message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,me);			
			me->move("/d/quanzhen/yuzhengong");	
			destruct(fbroom);
		}
		
		log_file("job/mgrqjob", sprintf("%8s%-10s抗敌蒙古入侵任务，离开失败，经验：%d。",
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
		write(HIY "你时间已过，任务失败。\n" NOR);
		me->add_condition("job_busy",60);		
		
		//销毁副本空间 
		if (fbroom) 
		{
			message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,me);			
			me->move("/d/quanzhen/yuzhengong");	
			destruct(fbroom);
		}
		
		
		log_file("job/mgrqjob", sprintf("%8s%-10s抗敌蒙古入侵任务，时间不够失败，经验：%d。",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		return 0;
	}
	//place=me->query_temp("qz/mgrqjob/place");
	//cplace=me->query_temp("qz/mgrqjob/cplace");
	
	if( me->query_temp("mgrq_job/enter") && environment(me) != fbroom)
	{
		if( !present( "menggu wushi", environment(me) ) && me->query_temp("mgrq_job/finish") )
	 	{
			
			//先奖励
		    give_raward(me);	 		
			return 0;
	 	}
		tell_object(me,HIY "你擅离职守，任务失败。\n" NOR);
		//销毁副本空间 
		if (fbroom) 
		{
			message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,me);			
			me->move("/d/quanzhen/yuzhengong");	
			destruct(fbroom);
		}
		log_file( "job/smy", sprintf("%8s%-10s抗敌蒙古入侵任务，离开失败，经验：%d。",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("mgrq_job");
		me->apply_condition("mgrq_job",-1);
		me->apply_condition("job_busy", 60);
		return 0;
		
	}	
	
	
	

	if(
		me->query_temp("mgrq_job/finish") >= 9 //更新成总共10组，以前是8组， by lsxk@hsbbs 2008/1/10
	 ///无具体实际限制 可以放大到9 .... and more
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
	 	///开始	 	
		me->set_temp("mgrq_job/enter",1);
		me->set_temp("mgrq_job/time",random(5));
	}
	if( duration < 5
	 && !me->query_temp("mgrq_job/enter") ){
		 
		 //销毁副本空间 
		if (fbroom) 
		{
			message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,me);			
			me->move("/d/quanzhen/yuzhengong");	
			destruct(fbroom);
		}	 
		 
		tell_object(me,HIY "你速度太慢，蒙古武士已过蒙古入侵，任务失败。\n" NOR);
		log_file( "job/mgrqjob", sprintf("%8s%-10s抗敌蒙古入侵任务，速度太慢失败，经验：%d。",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("mgrq_job");
		me->apply_condition("mgrq_job",-1);
		me->apply_condition("job_busy",60);
		return 0;
	}
	/*
	每间隔1 c 来一批 (恢复到7c)			
	玩家可以设置10 c 5c 用于走到smy
	5 c 进入准备状态
	*/
	if( environment(me) == me->query_temp("fbroom") && me->query_temp("mgrq_job") ){
		object npc;
		switch (duration){
			case 9:
			case 7:
				if ( random(80) >75 )
				message_vision(CYN "两名蒙古武士，缓缓经过山脚走了过来。\n" NOR, me);
				else if ( random(80) >50 )
				message_vision(BLU "远处传来一阵野兽的叫声，仔细听起来，仿佛狼嚎。\n" NOR, me);
				else
				message_vision(BLU + "山下的山谷传来一声凄厉的长啸，令人毛骨悚然。\n" NOR, me);
				break;
			case 5:	
				message_vision(BLU "一阵呼啸的山风刮过，山谷两侧的峭壁显得格外阴森。\n" NOR, me);
				break;			
			case 3:
				message_vision(CYN"远处的山脚下方传来一阵轻啸，隐约听得有人施展轻功飞驰而来。\n"NOR, me);
				break;
			case 1:	


                 if(present("menggu wushi", environment(me)))
	                   {
						   message_vision(CYN"$N动作太慢惊动了敌人，导致任务失败了。\n"NOR, me);
						   me->set_temp("mgrqfail",1);
						   return 1;
					   }
					   
				message_vision(CYN"下方的小路上闪出两条人影，$N纵身而起，立即和人影战在了一起。\n"NOR, me);
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
			tell_object(me,HIR "重新置5。\n" NOR);
		message("wizard", HIG"重新置5。\n"NOR, environment(me), me);
	}
	if (wizardp(me))
		tell_object(me,HIR "调试计时："+duration+"。\n" NOR);
	message("wizard", HIG"调试计时："+duration+"。\n"NOR, environment(me), me);
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
		me->set("job_name", "抗敌蒙古入侵");
		
          if(j ==1)
			 // TASKREWARD_D->get_reward(me,"蒙古入侵",1,1,x,0,1,1,0); 
             TASKREWARD_D->get_reward(me,"蒙古入侵",1,0,0,2,0,0,100); 		 
          else 
			 TASKREWARD_D->get_reward(me,"蒙古入侵",1,0,0,j+12,0,0,300);	
	   jobs=me->query("job_time/蒙古入侵");
	   if (random(jobs)>8000
			&& random(me->query("kar"))>27			
			&& !me->query("quest/qz/xtg/wuqi/start")
			&& (jobs % 50) ==0	
			&& me->query("quest/qz/dichuan"))
		{
			
				message_vision(HIC"郝大通在远处对$N竖起了大拇指，说道，“你如此辛苦为我大全真工作，真是不错”！\n"NOR,me);
				tell_object(me,me->query("name")+"，你不忙时候到我这里来，我看你这娃不错！\n");
				message("channel:rumor", HIM"【谣言】某人："+me->query("name")+"机缘巧合，获得郝大通的提点！\n"NOR, users());
				//message("channel:chat", HIC"【聊天】郝大通："+me->query("name")+"乃是我全真核心弟子，请江湖同道多多眷顾。！\n"NOR, users());
			
				me->set("quest/qz/xtg/wuqi/start",1);
		}
		
		if (environment(me) == fbroom) {				
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,me);
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
		me->clear_condition("mgrq_job");//防止Bug
}
