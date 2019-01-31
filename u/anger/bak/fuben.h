//fuben.h
aaa
q
q
a
//creat by renlai
#include <ansi.h>
void init()
{
	object me = this_player();		
	
	add_action("do_leave","leavefb");
	add_action("do_quit","quit");
	
	remove_call_out("fuben_reset");
	call_out("fuben_reset", 1900);
	
}

int do_quit()
{
	write("这里不能退出游戏。\n");	
	return 1;	
}

int do_leave()
{
	object me=this_player();
	object* team;
	
	team=me->query_team();	
	
	
	if(present("xixia wushi", environment(me)))
	{
		write("敌人没杀死还想跑?\n");	
		return 1;
	}
		
	
	if (team) 
	{
		
		if (team[0] != me) {
		  write("只有队长才能发指令离开。\n");	
		return 1;
	    }
		remove_call_out("fuben_reset");
	call_out("fuben_reset", 0);
	  //  fuben_reset();
		return 1;		
		
	}		
	else
	{
	remove_call_out("fuben_reset");
	call_out("fuben_reset", 0);
	  //  fuben_reset();
		return 1;		
	}
}

void fuben_reset()
{
	object *ob;
	int i;
	int nNPC=0,nPlayer=0,nDeleted=0;
	object room=this_object();
	ob = all_inventory(room);
	
	for( i=0; i < sizeof(ob); i++ )
	{
		
		 if(!userp(ob[i])){
					destruct(ob[i]);
					nDeleted++;
				}
		else {
			
		    message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,ob[i]);
			ob[i]->move(query("backroom"));//
		}
	}
   destruct(room);
}
