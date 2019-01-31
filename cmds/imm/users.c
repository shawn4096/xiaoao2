// info command.
// by snowman@SJ 1998.
//by renlai@xa2 2016 添加年卡月卡等在线数

#include <ansi.h>
#include <localtime.h>
inherit F_CLEAN_UP;
#include <canpian.h>

// #define TIME_TICK ((time()-945630720)*60)
mixed main(object me)
{
	object *ob;
	int i,ppl_cnt = 0, cnt = 0, wcnt = 0, f_cnt = 0, u_cnt = 0, i_cnt,scard=0,ycard=0,mcard=0,fcard=0,freeu=0;
    int hama3=0;
	string file;
	mapping *notes;
	mapping note;
	string test="suibo-zhuliu|dodge";
   string cur_value,next_value;
   string *myvalue;
   string* skilllist;
   object canpian;
	//ob = filter_array(objects(), (: userp :));
    ob=users();

	i = sizeof(ob);
	while( i-- ) {
		//&& (ob[i]->query("env/invisibility"))=="YES"
            if (wizardp(ob[i])) wcnt++;
		else if (interactive(ob[i])){
			 ppl_cnt++;
			 if(ob[i]->is_fighting()) f_cnt++;
			 if(!living(ob[i])) u_cnt++;
			 if(ob[i]->query("buyvip")) {ob[i]->delete("freeuser");scard++;}
			 if(ob[i]->query("y-card-vip")) {ob[i]->delete("freeuser");ycard++;}
			 if(ob[i]->query("m-card-vip")) {ob[i]->delete("freeuser");mcard++;}
			 if(ob[i]->query("freeuser")) freeu++;
			 if(query_idle(ob[i]) > 120) i_cnt++;
			 if(userp(ob[i])&& !wizardp(ob[i]) && !(ob[i]->query("no_pk")) && ob[i]->query("quest/hama/nizhuan/pass"))
             {
				 hama3++;
				 write(ob[i]->query("id"));		
                 //write("msg"+!ob[i]->query("no_pk"));					 
			 }				 
			 }
		else cnt++;
	}
	     fcard=ppl_cnt-scard-ycard-mcard-freeu;
		 if (fcard<0) fcard=0;
   
   
    
	
	
	
	
	write("\n"+MUD_NAME+"目前共有 "+wcnt+" 位巫师， "+ppl_cnt+" 位玩家连线中，"+cnt+" 位玩家断线中。
其中：
			在战斗的有： "+f_cnt+" 位。
			昏迷或睡觉的有： "+u_cnt+" 位。
			发呆的有： "+i_cnt+" 位。
			终身卡有： "+scard+" 位。
			年卡有： "+ycard+" 位。
			月卡有： "+mcard+" 位。
			免费玩家： "+freeu+" 位。
			注册中玩家： "+fcard+" 位。
			蛤蟆3玩家: "+hama3+" 位。
          
系统负担："+query_load_average()+"。
现在的 time() 是：" + time() + "。
现在的 Natured time() 是：" + TIME_TICK + " " + localtime(TIME_TICK)[2] + ":" + localtime(TIME_TICK)[1]+"。
现在的 uptime() 是：" + uptime() + "。
Natured 的时刻是：" + NATURE_D->query_daytime() + "。\n\n");
	return 1;
}




int help(object me)
{
write(@HELP
指令格式 : users

这个指令可以列出目前的玩家数量。

相关指令： who
HELP
	);
	return 1;
}
