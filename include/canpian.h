int dropcanpian(object me,int level);

mapping quest_skills = ([
"wuhu-duanmendao":5,
"jiuyin-baiguzhua":6,
"hujia-daofa":6,
"miaojia-jianfa":6,
"yangjia-qiang":7,
"anran-zhang":10,
]);

//残片掉落函数
int dropcanpian(object me,int level)
{	
	int x,y;
	object canpian;
	string* skilllist;
	string skillname;
	

   if (!me) return 0;   
   
	
   //只会掉落在列表里的
    skilllist=keys(quest_skills);//获取支持的skills
   
     if (me->query_temp("was_job/finish")) level=me->query_temp("was_job/finish");						 
			 
			 x=to_int(level/10);//10层开始掉落
		
			 switch (x) {
				 case 1:
				       if (!random(3))
					   {
						    skillname="wuhu-duanmendao";
						    y=1;
					   }
					   else return 0;
				       
					   break;                        
				 case 2:
				         if (!random(30))
					   {
						   if (random(2)) skillname="hujia-daofa";
						   else skillname="miaojia-jianfa";							   
						    y=1+random(2);
					   }
					   else return 0;
				       
					   break;                   
				         
				 case 3:
				       if (!random(20))
					   {
						    skillname=skilllist[random(x+1)];
						    y=1+random(3);
					   }
					   else return 0;
				       
					   break;                   
				         
				 case 4:
				      if (!random(10))
					   {
						    skillname=skilllist[random(x)+1];
						    y=1+random(quest_skills[skillname]);//获取碎片可选编号
					   }
					   else return 0;
					    break;
				case 5:
				      if (!random(20))
					   {
						    skillname=skilllist[random(x)+1];
						    y=2+random(quest_skills[skillname]-1);//获取碎片可选编号
					   }
					   else return 0;
					   break;                   
				 default:
				        return 0; 
				        break;                 						 
			 }
			 //第几片的某武功残片
			 if (!y || !skillname) return 0;
			 canpian = new("/u/anger/canpian");		         
	         canpian->set("owner",getuid(me));
             canpian->set_level(y,skillname);			 
	         canpian->move(me);
			 CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name()+"机缘巧合获得了"+to_chinese(skillname)+"之("+CHINESE_D->chinese_number(y)+")的残片。\n"NOR);
			 log_file("quest/canpian/获得"+to_chinese(skillname)+"残片_log",sprintf("%-18s成功获得%s之%s残片。\n",me->name(1)+"("+capitalize(getuid(me))+")",to_chinese(skillname),CHINESE_D->chinese_number(y)), me);	
             return 1;	
}