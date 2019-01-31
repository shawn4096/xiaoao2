
inherit ITEM;

#include <ansi.h>
#include <skill.h> 
#include <canpian.h>

string long();
void setbook(string skill,int level);
void initlvl();


void create()
{
	string name, id;
	
	set_name(HIW "武功秘籍残片" NOR, ({ "miji canpian","canpian"}));	
	
	
		set("unit", "张");
		set("no_beg", 1);
		set("no_give", 1);
		set("fb_item", 1);		
	
	setup();
	initlvl();
}

void initlvl()
{
	//if(clonep()) call_out("delete_owner",90+random(30));
}

int query_level()
{
	return query("level");
}


int set_level(int level,string vskillname)
{
	
	//这里会屏蔽不在列表里得技能，避免出问题
	
	string* skilllist;
	string skillname;
	int have=0;
	int maxnum=9;
	if (!level || !vskillname ) return 0;
	
	if (level<1 || level>20) level=1;
	
	        skilllist=keys(quest_skills);//获取支持的skills
			
			for (int i=0;i<sizeof(skilllist);i++)
			{
				if (skilllist[i]==vskillname) {					
					have=1;
					skillname=vskillname;
					break;
				}                				
			}
			
			if (!have) {
				skillname=skilllist[0];//若是不在列表里，则取第一位				
			}
			
			maxnum=quest_skills[skillname];	
			
			switch(maxnum) {
		       case 5:		       
			        
				       set("name",GRN"《"+to_chinese(skillname)+"》残片之("+CHINESE_D->chinese_number(level)+")"NOR);
	                
				break;
				case 6:
		               set("name",HIB"《"+to_chinese(skillname)+"》残片之("+CHINESE_D->chinese_number(level)+")"NOR);
			  
				break;
				case 7:
		               set("name",HIB"《"+to_chinese(skillname)+"》残片之("+CHINESE_D->chinese_number(level)+")"NOR);
			  
				break;
				case 10:
		               set("name",HIY"《"+to_chinese(skillname)+"》残片之("+CHINESE_D->chinese_number(level)+")"NOR);
			  
				break;		
				default:
		               set("name",WHT"《"+to_chinese(skillname)+"》残片之("+CHINESE_D->chinese_number(level)+")"NOR);			 
				break;
			}
			
	        set("long","《"+to_chinese(skillname)+"》残片之("+CHINESE_D->chinese_number(level)+"),共"+CHINESE_D->chinese_number(maxnum)+"片。收集齐后再合并(hebing skillsname)，便可以学习。\n");
			set("level",level);//残片编号
	        set("skillname",skillname);//残片所有技能	       
	        set("maxnum",maxnum);//残片总数	
			return 1;   	
	
	
}

void init()
{
	object me = this_player(), ob;

	if ( environment() == me && !query("unique")) {		
		add_action("do_hebing", "hebing");
	}
	if (query("owner") == getuid(me)) return;
	//ob = find_player(query("owner"));
	//if ( ! ob) return;	
	return;
}

int do_hebing(string arg)
{
	object me = this_player();
    object obj;
	object* obs;
	int max;
	
	if (!me) return;
	if (!arg) return notify_fail("你要合并什么。\n");
    if (query("skillname")!=arg) return notify_fail("你没有这个残片。\n");
	
	if (!query("owner")) return notify_fail("这个残片不是你的，你从什么地方得到的？\n"); 
	
	if ( query("owner") != getuid(me)) return notify_fail("这个残片不是你的，你从什么地方得到的？\n");
	
	if (!query("maxnum")) notify_fail("你的残片有问题。\n");
	
	max=query("maxnum");
	
	me->delete_temp("miji");//删除标记
	
	obs = filter_array(all_inventory(me),(:$1->query("fb_item"):));
	
	
	if (sizeof(obs)<max) notify_fail("你的残片尚未收集齐。\n");
	
	if(sizeof(obs)){
		    //先在玩家身上标记
			for(int j=0;j<sizeof(obs);j++) 
			{
				if (obs[j]->query("owner")!= getuid(me))
				{
					destruct(obs[j]);
					return notify_fail("这个残片不是你的，你从什么地方得到的？\n");
				}
				
				if (obs[j]->query("skillname")==arg)
				{				
				  me->set_temp("miji/"+obs[j]->query("skillname")+"/"+obs[j]->query_level(),1);				  
				}			
			}
          //再对比是否缺少 从1开始
		  for (int i=1;i<=max;i++)
		  {
			  if (!me->query_temp("miji/"+arg+"/"+i)) {
                   me->delete_temp("miji/"+arg);//删除标记
				  return notify_fail("你的"+to_chinese(arg)+"还缺残片之"+CHINESE_D->chinese_number(i)+"。\n");
			  }
		  }
		  
		  
		    me->delete_temp("miji");
		    me->set("miji/"+arg+"/pass",1);
            
			set("owner",getuid(me));			
            setbook(arg,100);//先设置100
            for(int j=0;j<sizeof(obs);j++) 
			{
				if (obs[j]->query("skillname")==arg)
				{				
				   destruct(obs[j]);
				}			
			}


            //这里设置一些特殊skills的标记需求
	switch(arg) {
		case "wuhu-duanmendao":
		        me->set("mao18/pass",1);//五虎1的标记
				setbook(arg,100);//先设置100
		break;
		
		case "jiuyin-baiguzhua":
                me->set("quest/jiuyin2/pass",1);		
				setbook(arg,200);//先设置100		
		break;
		
		case "miaojia-jianfa":
               me->set("quest/雪山飞狐/武功/miaojiajianfa",1);		
			   setbook(arg,200);//先设置100		
		break;
		
		case "hujia-daofa":
                 me->set("quest/雪山飞狐/武功/hujiadaofa",1);		
				 setbook(arg,200);//先设置100		
		break;
        case "anran-zhang":
		      me->set("quest/anran/pass",1);
			  setbook(arg,200);//先设置100
        break;	
		case "yangjia-qiang":
		      me->set("quest/射雕英雄传/yangjiaqiang/pass",1);
			  setbook(arg,200);//先设置100
        break;		
	}        	
			
			write("你将这数张千辛万苦才收集齐全的残卷装订成册，并细心用线装订起来。\n");
			CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name()+"成功收集齐"+to_chinese(arg)+"残片，并拼出了"+to_chinese(arg)+"的完整秘籍。\n"NOR);
			message_vision(HIG+me->name()+"成功收集齐残片，并拼出了"+to_chinese(arg)+"的完整秘籍。\n"NOR,me);            
			log_file("quest/canpian/合成"+to_chinese(arg)+"_log",sprintf("%-18s成功合并%s。\n",me->name(1)+"("+capitalize(getuid(me))+")",to_chinese(arg)), me);			
			return 1;	
		}	
	return 0;
}



//这里以后设置各种skills的预定值和标记

void setbook(string skill,int level)
{
	string* skilllist;
	int titlelevel;
	
	
	//获取武技的最大数，确定等级	
	titlelevel=quest_skills[skill];
	
	switch(titlelevel) {
		case 5:		       
			  set_name(GRN+to_chinese(skill)+"秘籍" NOR, ({ "mi ji", "miji", "book", "shu" }));
		      break;
		case 6:
		      // BLU
			  set_name(BLU+to_chinese(skill)+"秘籍"NOR, ({ "mi ji", "miji", "book", "shu" }));
		break;
		case 7:
		      // BLU
			  set_name(BLU+to_chinese(skill)+"秘籍"NOR, ({ "mi ji", "miji", "book", "shu" }));
		break;
		case 10:
		      // HIY
			  set_name(HIY+to_chinese(skill)+"秘籍"NOR, ({ "mi ji", "miji", "book", "shu" }));
		break;		
		default:
		      // WHT
			  set_name(WHT+to_chinese(skill)+"秘籍"NOR, ({ "mi ji", "miji", "book", "shu" }));
		break;
	}
	
	
	
	set("unit", "本");
	set("long", "这是一本由数张残卷汇集而成的线装书。\n");
	set("unique", 1);
	set("material", "paper");
	delete("skillname");//删除标记
	delete("maxnum");
	delete("level");
	delete("fb_item");
	remove_action("do_hebing","hebing");//删除残卷标记		
	
	set("skill", ([
			"name":	skill,	// name of the skill
			"exp_required":	10000000,	// minimum combat experience required
			"jing_cost":	100,	// jing cost every time study this
			"difficulty":	35,	// the base int to learn this skill
			"max_skill":	level // the maximum level you can learn
		]) );
}

