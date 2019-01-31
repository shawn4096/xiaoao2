
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
	
	set_name(HIW "�书�ؼ���Ƭ" NOR, ({ "miji canpian","canpian"}));	
	
	
		set("unit", "��");
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
	
	//��������β����б���ü��ܣ����������
	
	string* skilllist;
	string skillname;
	int have=0;
	int maxnum=9;
	if (!level || !vskillname ) return 0;
	
	if (level<1 || level>20) level=1;
	
	        skilllist=keys(quest_skills);//��ȡ֧�ֵ�skills
			
			for (int i=0;i<sizeof(skilllist);i++)
			{
				if (skilllist[i]==vskillname) {					
					have=1;
					skillname=vskillname;
					break;
				}                				
			}
			
			if (!have) {
				skillname=skilllist[0];//���ǲ����б����ȡ��һλ				
			}
			
			maxnum=quest_skills[skillname];	
			
			switch(maxnum) {
		       case 5:		       
			        
				       set("name",GRN"��"+to_chinese(skillname)+"����Ƭ֮("+CHINESE_D->chinese_number(level)+")"NOR);
	                
				break;
				case 6:
		               set("name",HIB"��"+to_chinese(skillname)+"����Ƭ֮("+CHINESE_D->chinese_number(level)+")"NOR);
			  
				break;
				case 7:
		               set("name",HIB"��"+to_chinese(skillname)+"����Ƭ֮("+CHINESE_D->chinese_number(level)+")"NOR);
			  
				break;
				case 10:
		               set("name",HIY"��"+to_chinese(skillname)+"����Ƭ֮("+CHINESE_D->chinese_number(level)+")"NOR);
			  
				break;		
				default:
		               set("name",WHT"��"+to_chinese(skillname)+"����Ƭ֮("+CHINESE_D->chinese_number(level)+")"NOR);			 
				break;
			}
			
	        set("long","��"+to_chinese(skillname)+"����Ƭ֮("+CHINESE_D->chinese_number(level)+"),��"+CHINESE_D->chinese_number(maxnum)+"Ƭ���ռ�����ٺϲ�(hebing skillsname)�������ѧϰ��\n");
			set("level",level);//��Ƭ���
	        set("skillname",skillname);//��Ƭ���м���	       
	        set("maxnum",maxnum);//��Ƭ����	
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
	if (!arg) return notify_fail("��Ҫ�ϲ�ʲô��\n");
    if (query("skillname")!=arg) return notify_fail("��û�������Ƭ��\n");
	
	if (!query("owner")) return notify_fail("�����Ƭ������ģ����ʲô�ط��õ��ģ�\n"); 
	
	if ( query("owner") != getuid(me)) return notify_fail("�����Ƭ������ģ����ʲô�ط��õ��ģ�\n");
	
	if (!query("maxnum")) notify_fail("��Ĳ�Ƭ�����⡣\n");
	
	max=query("maxnum");
	
	me->delete_temp("miji");//ɾ�����
	
	obs = filter_array(all_inventory(me),(:$1->query("fb_item"):));
	
	
	if (sizeof(obs)<max) notify_fail("��Ĳ�Ƭ��δ�ռ��롣\n");
	
	if(sizeof(obs)){
		    //����������ϱ��
			for(int j=0;j<sizeof(obs);j++) 
			{
				if (obs[j]->query("owner")!= getuid(me))
				{
					destruct(obs[j]);
					return notify_fail("�����Ƭ������ģ����ʲô�ط��õ��ģ�\n");
				}
				
				if (obs[j]->query("skillname")==arg)
				{				
				  me->set_temp("miji/"+obs[j]->query("skillname")+"/"+obs[j]->query_level(),1);				  
				}			
			}
          //�ٶԱ��Ƿ�ȱ�� ��1��ʼ
		  for (int i=1;i<=max;i++)
		  {
			  if (!me->query_temp("miji/"+arg+"/"+i)) {
                   me->delete_temp("miji/"+arg);//ɾ�����
				  return notify_fail("���"+to_chinese(arg)+"��ȱ��Ƭ֮"+CHINESE_D->chinese_number(i)+"��\n");
			  }
		  }
		  
		  
		    me->delete_temp("miji");
		    me->set("miji/"+arg+"/pass",1);
            
			set("owner",getuid(me));			
            setbook(arg,100);//������100
            for(int j=0;j<sizeof(obs);j++) 
			{
				if (obs[j]->query("skillname")==arg)
				{				
				   destruct(obs[j]);
				}			
			}


            //��������һЩ����skills�ı������
	switch(arg) {
		case "wuhu-duanmendao":
		        me->set("mao18/pass",1);//�廢1�ı��
				setbook(arg,100);//������100
		break;
		
		case "jiuyin-baiguzhua":
                me->set("quest/jiuyin2/pass",1);		
				setbook(arg,200);//������100		
		break;
		
		case "miaojia-jianfa":
               me->set("quest/ѩɽ�ɺ�/�书/miaojiajianfa",1);		
			   setbook(arg,200);//������100		
		break;
		
		case "hujia-daofa":
                 me->set("quest/ѩɽ�ɺ�/�书/hujiadaofa",1);		
				 setbook(arg,200);//������100		
		break;
        case "anran-zhang":
		      me->set("quest/anran/pass",1);
			  setbook(arg,200);//������100
        break;	
		case "yangjia-qiang":
		      me->set("quest/���Ӣ�۴�/yangjiaqiang/pass",1);
			  setbook(arg,200);//������100
        break;		
	}        	
			
			write("�㽫������ǧ�������ռ���ȫ�Ĳо�װ���ɲᣬ��ϸ������װ��������\n");
			CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name()+"�ɹ��ռ���"+to_chinese(arg)+"��Ƭ����ƴ����"+to_chinese(arg)+"�������ؼ���\n"NOR);
			message_vision(HIG+me->name()+"�ɹ��ռ����Ƭ����ƴ����"+to_chinese(arg)+"�������ؼ���\n"NOR,me);            
			log_file("quest/canpian/�ϳ�"+to_chinese(arg)+"_log",sprintf("%-18s�ɹ��ϲ�%s��\n",me->name(1)+"("+capitalize(getuid(me))+")",to_chinese(arg)), me);			
			return 1;	
		}	
	return 0;
}



//�����Ժ����ø���skills��Ԥ��ֵ�ͱ��

void setbook(string skill,int level)
{
	string* skilllist;
	int titlelevel;
	
	
	//��ȡ�似���������ȷ���ȼ�	
	titlelevel=quest_skills[skill];
	
	switch(titlelevel) {
		case 5:		       
			  set_name(GRN+to_chinese(skill)+"�ؼ�" NOR, ({ "mi ji", "miji", "book", "shu" }));
		      break;
		case 6:
		      // BLU
			  set_name(BLU+to_chinese(skill)+"�ؼ�"NOR, ({ "mi ji", "miji", "book", "shu" }));
		break;
		case 7:
		      // BLU
			  set_name(BLU+to_chinese(skill)+"�ؼ�"NOR, ({ "mi ji", "miji", "book", "shu" }));
		break;
		case 10:
		      // HIY
			  set_name(HIY+to_chinese(skill)+"�ؼ�"NOR, ({ "mi ji", "miji", "book", "shu" }));
		break;		
		default:
		      // WHT
			  set_name(WHT+to_chinese(skill)+"�ؼ�"NOR, ({ "mi ji", "miji", "book", "shu" }));
		break;
	}
	
	
	
	set("unit", "��");
	set("long", "����һ�������Ųо�㼯���ɵ���װ�顣\n");
	set("unique", 1);
	set("material", "paper");
	delete("skillname");//ɾ�����
	delete("maxnum");
	delete("level");
	delete("fb_item");
	remove_action("do_hebing","hebing");//ɾ���о���		
	
	set("skill", ([
			"name":	skill,	// name of the skill
			"exp_required":	10000000,	// minimum combat experience required
			"jing_cost":	100,	// jing cost every time study this
			"difficulty":	35,	// the base int to learn this skill
			"max_skill":	level // the maximum level you can learn
		]) );
}

