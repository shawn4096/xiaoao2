int dropcanpian(object me,int level);

mapping quest_skills = ([
"wuhu-duanmendao":5,
"jiuyin-baiguzhua":6,
"hujia-daofa":6,
"miaojia-jianfa":6,
"yangjia-qiang":7,
"anran-zhang":10,
]);

//��Ƭ���亯��
int dropcanpian(object me,int level)
{	
	int x,y;
	object canpian;
	string* skilllist;
	string skillname;
	

   if (!me) return 0;   
   
	
   //ֻ��������б����
    skilllist=keys(quest_skills);//��ȡ֧�ֵ�skills
   
     if (me->query_temp("was_job/finish")) level=me->query_temp("was_job/finish");						 
			 
			 x=to_int(level/10);//10�㿪ʼ����
		
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
						    y=1+random(quest_skills[skillname]);//��ȡ��Ƭ��ѡ���
					   }
					   else return 0;
					    break;
				case 5:
				      if (!random(20))
					   {
						    skillname=skilllist[random(x)+1];
						    y=2+random(quest_skills[skillname]-1);//��ȡ��Ƭ��ѡ���
					   }
					   else return 0;
					   break;                   
				 default:
				        return 0; 
				        break;                 						 
			 }
			 //�ڼ�Ƭ��ĳ�书��Ƭ
			 if (!y || !skillname) return 0;
			 canpian = new("/u/anger/canpian");		         
	         canpian->set("owner",getuid(me));
             canpian->set_level(y,skillname);			 
	         canpian->move(me);
			 CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name()+"��Ե�ɺϻ����"+to_chinese(skillname)+"֮("+CHINESE_D->chinese_number(y)+")�Ĳ�Ƭ��\n"NOR);
			 log_file("quest/canpian/���"+to_chinese(skillname)+"��Ƭ_log",sprintf("%-18s�ɹ����%s֮%s��Ƭ��\n",me->name(1)+"("+capitalize(getuid(me))+")",to_chinese(skillname),CHINESE_D->chinese_number(y)), me);	
             return 1;	
}