inherit NPC;
#include <ansi.h>

//ob->query("birthday")< =1305041966


int ask_bagua();
int ask_liwu();
int ask_chunjie();
int ask_quanfa();
int ask_jiangli();
int ask_vip();
int ask_down();
int ask_down1();

int ask_qingming();
int ask_51();
int ask_zhongqiu();
int ask_nianka();
int ask_guoqing();
int ask_xiaonian();
int ask_yuanxiao();
int ask_yueka();
int ask_downji();
int ask_title();
int ask_duanwu();
int do_answer(string arg);
void create()
{
        set_name("��ʦ",({  "wizard", "wushi" }) );
        set("gender", "����" );
        set("age", 30);
        set("long", "����һ��Ц��������ʦ���ٻ���������ʦ��ż��Э����ʦ�����£��󲿷ֵ�ʱ�䶼���������¡�\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
        set("combat_exp", 100);
        set("attitude", "peaceful");
        setup();

        set("inquiry", ([
            //  "2018Ԫ������":   (: ask_liwu  :),
		  //"С������":   (: ask_xiaonian  :),
		//	"Ԫ���ڴ���Բ��Ԫ���ȶ���͹�����Բ��":   (: ask_yuanxiao  :),

			  //"ף��2018�깷�����˴󼪴���":   (: ask_chunjie  :),
	//			   "�����ھ���͵ڶ���崻�����":   (: ask_qingming  :),
         //     "����һ�Ͷ��ڼ�ֹһ����ֵܽ����¾�":   (: ask_51  :),
			//   "�꿨���":   (: ask_nianka  :),
			  "�¿����":   (: ask_yueka  :),
             // "���Ű���":   (: ask_bagua   :),
             // "����ȭ��":   (: ask_quanfa  :),
		//	  "�����±�":   (: ask_zhongqiu  :),
              //"���ֽ���":   (: ask_jiangli :),
              //"���ר��":   (: ask_vip :),
			   "��������￪��":   (: ask_guoqing :),
			//	"���������":   (: ask_duanwu :),
    //          "����������һ��":   (: ask_down1 :),
			//"�ָ�����":   (: ask_title :),
		//	"��������":   (: ask_downji :),
        ]) );

        carry_object("/clone/misc/cloth")->wear();
}
int ask_title()
{
	object me=this_player();
	message_vision(HIM"$Nֻ�ܻ�����Ѿ����ܺ��title,��ָ�ʲôtitle?�������˿�������"HIC"(answer xxxx)"HIM"�Ϳ�����!\n"+
					"��ǰ����ѡ��Ϊ��������:\n"+
					HIC"\t\t\t�����澭�ϲ�----answer �����澭\n"+
					HIC"\t\t\t�貨΢��--------answer �貨΢��\n"+
					HIC"\t\t\t����׷�����--------answer ����׷�����\n"+
					HIC"\t\t\t���Ǵ��ں�--------answer ���Ǵ��ں�\n"+
					HIC"\t\t\tȫ���ƽ�--------answer ȫ���ƽ�\n"NOR,me);
	add_action("do_answer","answer");
	return 1;

	

}
int do_answer(string arg)
{
	object me=this_player();

	if (!arg) return notify_fail("�����Ķ�߽��ʲô�أ�\n");
	switch (arg)
	   
	{
		case "�貨΢��":
			if ( me->query("quest/�����˲�/�书/pass")&& me->query("quest/�����˲�/�书/read"))
			{
				  me->set("title",HIC"�貨"HIW"΢��"HIG"����"NOR);
				  message_vision(HIC"$n��$N������Ľ֮ɫ�����˸��򸣺���Ц���������ǹ�ϲ���ˣ�������ô�ѵ����ⶼ�ܽ⿪�������������޵�\n"NOR,me,this_object());
				  return 1;
			}else {
			   message_vision(HIY"$n����$N��ɧ�Ų������ǣ�������ŭ������֮ɫ�������ϣ�˵�������������ģ�����������\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n�ǳ������Ķ�$N˵�����ҿ�����ǳ�����ɧ���ҵģ����������ȥ�ɣ�\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			break;
		case "����ʮ����":
			if (me->query("xlz/sanzhao","pass"))
			{
				  me->set("title",HIC"��ؤ"HIY"����ֿ��"NOR);
				  message_vision(HIC"$n��$N������Ľ֮ɫ�����˸��򸣺���Ц���������ǹ�ϲ���ˣ�������ô�ѵ����ⶼ�ܽ⿪�������������޵�\n"NOR,me,this_object());
				  return 1;
				  
			}else {
			   message_vision(HIY"$n����$N��ɧ�Ų������ǣ�������ŭ������֮ɫ�������ϣ�˵�������������ģ�����������\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n�ǳ������Ķ�$N˵�����ҿ�����ǳ�����ɧ���ҵģ����������ȥ�ɣ�\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			break;
			case "ȫ���ƽ�":
			if (me->query("quanzhen/force","pass"))
			{
				  me->set("title",HIB"ȫ��� �ƽ�����"NOR);
				  message_vision(HIC"$n��$N������Ľ֮ɫ�����˸��򸣺���Ц�����������ƽ����ˡ�\n"NOR,me,this_object());
				  return 1;
				  
			}else {
			   message_vision(HIY"$n����$N��ɧ�Ų������ǣ�������ŭ������֮ɫ�������ϣ�˵�������������ģ�����������\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n�ǳ������Ķ�$N˵�����ҿ�����ǳ�����ɧ���ҵģ����������ȥ�ɣ�\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			
			case "����׷�����":
			if (me->query("quest/xx/tsz/zhuihun/pass"))
			{
				   me->set("title",HIB"������ ׷�������"NOR);
				  message_vision(HIC"$n��$Nһ������֮ɫ������һ��������˵����������������\n"NOR,me,this_object());
				  return 1;
				  
			}else {
			   message_vision(HIY"$n����$N��ɧ�Ų������ǣ�������ŭ������֮ɫ�������ϣ�˵�������������ģ�����������\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n�ǳ������Ķ�$N˵�����ҿ�����ǳ�����ɧ���ҵģ����������ȥ�ɣ�\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			case "���Ǵ��ں�":
			if (me->query("quest/xxdf/pass")==2)
			{
				  me->set("title",HIC"�������"HIB"���Ǵ󷨴���"NOR);
				  message_vision(HIC"$n��$Nһ������֮ɫ�����ĵ�˵���������ߣ����ߡ�\n"NOR,me,this_object());
				  return 1;
				  
			}else {
			   message_vision(HIY"$n����$N��ɧ�Ų������ǣ�������ŭ������֮ɫ�������ϣ�˵�������������ģ�����������\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n�ǳ������Ķ�$N˵�����ҿ�����ǳ�����ɧ���ҵģ����������ȥ�ɣ�\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			break;

	}
	return 1;



}

int ask_downji()
{      
       object me = this_player();
       if ((me->query("m-card-vip") ||me->query("registered")<3 )&&me->query("combat_exp")<1500000)
       {
		   command("say �¿��Լ����������Ҿ���ֵ����1.5m�������Ŭ�������������õ��ˡ���\n");
		   return 1;
       }
	   if( !me->query("liwu/downji")  )
		{ 
                 command("giggle");
				 command("say ǰ����Ƶ��down���������������ʧ������wiz���һ�����⡣");
				//me->add("combat_exp",80000);
                 me->add("SJ_Credit",1000); 
				 me->add("potential",250000);
				 me->add("balance",10000000);
                 tell_object(me, HIG"���ǹ����ң�����"+ HIR + chinese_number(250000) + CYN +"�㡸"+HIG+"Ǳ��"+CYN+"����\n"NOR);
                 tell_object(me, HIG"������"+ HIR + chinese_number(1000) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
				 tell_object(me, HIG"������"+ HIC + chinese_number(1000) + HIC +"����"+HIG+"�ƽ�"+CYN+"����\n"NOR);

				 tell_object(me, HIM"��õ����齣Ц��������ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR);    
				// me->add("ggs/left_time",1080000);
                                            
				me->set("liwu/downji",1);         
                CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ��崻��������\n"NOR);
                         
               return 1;
       }
       else {
                 command("kick "+me->query("id"));
                 command("say �㲻���Ѿ�����ˣ�");
                 return 1;
       }
      

}
int ask_down1()
{      
       object me = this_player();
       if (me->query("id")=="missyou" ||me->query("id")=="tiandi")
       {
		   command("say "+me->query("name")+"���汧Ǹ�����Ѿ�����ˡ�\n");
		   return 1;	 
	   }
	   if( !me->query("liwu/down1")  )
		{ 
                 command("giggle");
				 command("say ǰ����Ƶ��down���������������ʧ������wiz���һ�����⡣");
				//me->add("combat_exp",80000);
                 me->add("SJ_Credit",500); 
				 me->add("potential",250000);
                 tell_object(me, HIG"���ǹ����ң�����"+ HIR + chinese_number(250000) + CYN +"�㡸"+HIG+"Ǳ��"+CYN+"����\n"NOR);
                 tell_object(me, HIG"������"+ HIR + chinese_number(500) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
				 tell_object(me, HIM"��õ����齣Ц��������ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR);    
				 me->add("ggs/left_time",1080000);
                                            
				me->set("liwu/down1",1);         
                CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ��崻�������һ�����\n"NOR);
                         
               return 1;
       }
       else {
                 command("kick "+me->query("id"));
                 command("say �㲻���Ѿ�����ˣ�");
                 return 1;
       }
      

}
/*
int ask_down()
{      
       object me = this_player();
       
        if(me->query("birthday",1) <= 1305377084 ){   
        if( !me->query("down_ext1") )  { 
                                  command("say ǰ����Ƶ��down���������������ʧ������wiz���һ�����⡣");

                 if(me->query("buyvip")) { me->add("combat_exp",150000);
                                           me->add("SJ_Credit",500); 

                                       tell_object(me, HIG"�������������ң�����"+ HIR + chinese_number(150000) + CYN +"�㡸"+HIG+"ʵս����"+CYN+"����\n"NOR);
                                       tell_object(me, HIG"������"+ HIR + chinese_number(500) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
                                          }
            else if(me->query("y-card-vip"))
                                         { me->add("combat_exp",100000);
                                           me->add("SJ_Credit",450); 

                                      tell_object(me, HIG"�����꿨��ң�����"+ HIR + chinese_number(100000) + CYN +"�㡸"+HIG+"ʵս����"+CYN+"����\n"NOR);
                                      tell_object(me, HIG"������"+ HIR + chinese_number(450) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
                                          }

           else if(me->query("registered")==3 ){ me->add("combat_exp",80000);
                                                 me->add("SJ_Credit",400); 

                                     tell_object(me, HIG"���ǹ����ң�����"+ HIR + chinese_number(80000) + CYN +"�㡸"+HIG+"ʵս����"+CYN+"����\n"NOR);
                                     tell_object(me, HIG"������"+ HIR + chinese_number(400) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
                                                }
               me->set("down_ext1",1);         
                             me->delete("down_ext",1);            
               return 1;
                                           }
 


       else {
                 command("kick "+me->query("id"));
                 command("say �㲻���Ѿ�����ˣ�");
                                              me->delete("down_ext",1);            
                 return 1;
            }
         }
       else 
         {    command("kick "+me->query("id"));
              command("say ��ѻ�죡downʲô����");
                                           me->delete("down_ext",1);            
               return 1; }

}

int ask_bagua()
{      
       mapping myfam;    
       object me = this_player();
       myfam = (mapping)me->query("family");

       if(!myfam || myfam["family_name"] != "�һ���")
        {   
           if( !me->query_skill("qimen-bagua") || me->query_skill("qimen-bagua",1) < 30 )         
             { 
               command("say �ðɣ��ҿ��Խ���һ�����Ű��Ե�ѧ�ʡ�");
               me->set_skill("qimen-bagua", 50);
               return 1;
              }
           else {
                command("say ���Ѿ���?��Ե��ˣ��ҿɽ̲�����ʲô�����?);  
                 return 1; 
                  }
         }
         else 
         {    command("kick "+me->query("id"));
              command("say �㲻ȥ����ʦ���ú�ѧϰ����Ͷ��ȡ�ɰ���");
               return 1; }

}*/
int ask_xiaonian()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
	 if( me->query("liwu/xiaonian") ) 
     {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
     }

     if( me->query("combat_exp") < 150000 ) 
     {
          command("say 150k����н��������ʵս���鲻�㣬����ץ��ʱ��ȥ�����ɣ����˾Ϳ������ˡ�");
          return 1;
     }

     command("say Ϊ������齣Ц������վ2015��С��ĵ�������ʦ��������ֵܽ��Ƿ�������");
	 command("say �����ֵܽ���С����֣����彡����ȫ���Ҹ�����ߣ����ɡ�");
     command("say ��л����֧�֣�ϣ������Ŀ��ģ���ĳ��ã�");
	 command("say С��");
	 command("say �꣡");
	 command("say �죡");
	 command("say �֣�");
     me->set("liwu/xiaonian",1);
     me->add("SJ_Credit",500);
     me->add("balance", 1000000);
	 //me->add("balance", 10000000);
     tell_object(me, HIR"\n\n\n�µ�һ���ر��л��ЩΪЦ�������ṩ��������ң���������ɰ����ˣ�\n\n\n"NOR);
     tell_object(me, HIC"\n\n\nԶ��quest,����˶����չ˼��ˣ��ذ��Լ���\n\n\n"NOR);

     tell_object(me, HIG"��õ����齣Ц��������ף�������"+ HIR + chinese_number(500) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
     tell_object(me, HIG"��õ����齣Ц����������� " + MONEY_D->money_str(1000000) + "��\n"NOR);
     tell_object(me, HIM"��õ����齣?���������ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR);    
     me->add("ggs/left_time",1080000);
	 /*
	 tell_object(me, HIR"��õ����齣Ц��������ף�����������൱�൱����˫������ֵʱ�䣡��Թ�����Ͻ��һ���\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
	 else
                me->add_condition("db_exp", 10000);
*/
     CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ�ݷ������\n"NOR);
    return 1;
}
int ask_guoqing()
{
  
    object me = this_player(); 
	object obj;
   //if( me->query("start_liwu") ) 
	 if( me->query("liwu/guoqing18") ) 
       {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
       }   

     command("say Ϊ������齣Ц������վ2018������+����ڵĵ�������ʦ��������ֵܽ��Ƿ�������");
	 command("say �����ֵܽ�������ѽڣ����彡����ȫ���Ҹ���");
     command("say ��л����֧�֣�ϣ������Ŀ��ģ���ĳ��ã�");
	 command("say ����");
	 command("say �죡");
	 command("say �У�");
	 command("say �");
	 command("say �죡");
	 command("say �֣�");

     me->set("liwu/guoqing18",1);    
	
	obj = new(__DIR__"obj/yuebing");
	 obj->set("owner",me->query("id"));
	 obj->set("date_item",1);//���������ǣ�����clone
     obj->move(me);
	 CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ�������±���\n"NOR);
    return 1;
}
//�����
int ask_duanwu()
{
	object me = this_player(); 
	object obj;
	 if( me->query("liwu/duanwu") ) 
       {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
       }
	 command("say Ϊ������齣Ц������վ2017�����ڵĵ�������ʦ��������ֵܽ��Ƿ�������");
	 command("say �����ֵܽ��ö���ѽڣ����彡����ȫ���Ҹ�����ߣ����ɡ�");
	 command("say ��ס����������й��Ĵ�ͳ���գ��Ǹ���ԭ�����ڴ�����������");

     command("say ��л����֧�֣�ϣ������Ŀ��ģ���ĳ��ã�");
	 command("say �ˣ�");
	 command("say �磡");
	 command("say �죡");
	 command("say �֣�");
     me->set("liwu/duanwu",1);
	 obj = new(__DIR__"obj/zongzi");
	 obj->set("owner",me->query("id"));
	 obj->set("date_item",1);//���������ǣ�����clone
     obj->move(me);
	 CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ�Ŷ������ӣ�\n"NOR);	 
  
   return 1;
}
int ask_zhongqiu()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
	 if(me->query("liwu/zhongqiu16") ) 
       {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
       }   

     command("say Ϊ������齣Ц������վ2016������ڵĵ�������ʦ��������ֵܽ��Ƿ�������");
	 command("say �����ֵܽ�������ѽڣ����彡����ȫ���Ҹ�����ߣ����ɡ�");
     command("say ��л����֧�֣�ϣ������Ŀ��ģ���ĳ��ã�");
	 command("say �У�");
	 command("say �");
	 command("say �죡");
	 command("say �֣�");
     me->set("liwu/zhongqiu16",1);
     me->add("SJ_Credit",2000);
     //me->add("balance", 10000000);
	 me->add("balance", 10000000);
     tell_object(me, HIR"\n\n\n�µ�һ���ر��л��ЩΪЦ�������ṩ��������ң���������ɰ����ˣ�\n\n\n"NOR);
     tell_object(me, HIC"\n\n\nԶ��quest,����˶����չ˼��ˣ��ذ��Լ���\n\n\n"NOR);

     tell_object(me, HIG"��õ����齣Ц��������ף�������"+ HIR + chinese_number(2000) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
     tell_object(me, HIG"��õ����齣Ц����������� " + MONEY_D->money_str(10000000) + "��\n"NOR);
     tell_object(me, HIM"��õ����齣Ц��������ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR);    
   //  me->add("ggs/left_time",1080000);
	 tell_object(me, HIR"��õ����齣Ц��������ף�����������൱�൱����˫������ֵʱ�䣡��pk���Ͻ��һ���\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
		else
                me->add_condition("db_exp", 10000);

     CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ�ݷ������\n"NOR);
    return 1;
}
//Ԫ��
int ask_liwu()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
	 if( me->query("yuandan_2018") ) 
       {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
       }


   if( me->query("combat_exp") < 100000 ) 
       {
          command("say 100k����н��������ʵս���鲻�㣬����ץ��ʱ��ȥ�����ɣ����˾Ϳ������ˡ�");
          return 1;
       }

     command("say Ϊ������齣Ц������վ2018��Ԫ���ĵ�������ʦ��������ֵܽ��Ƿ�������");
	 command("say �����ֵܽ������µ�һ������彡����ȫ���Ҹ���");
	// command("say ���У�ǰһ�׶�Ƶ�������������ײ�����Ĳ�����崻���һ�����貹������ʦ��������ֵܽ����ٷ�������");
     //command("say ��л����֧�֣�ϣ������Ŀ��ģ���ĳ��ã�");
     me->set("yuandan_2018",1);
     me->add("SJ_Credit",1000);
     //me->add("balance", 10000000);
	 //me->add("balance", 10000000);
     tell_object(me, HIR"\n\n\n�µ�һ���ر��л��ЩΪЦ�������ṩ��������ң���������ɰ����ˣ�\n\n\n"NOR);
     tell_object(me, HIC"\n\n\nԶ��quest,����˶����չ˼��ˣ��ذ��Լ���\n\n\n"NOR);

     tell_object(me, HIG"��õ����齣Ц��������ף�������"+ HIR + chinese_number(1000) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
   //  tell_object(me, HIG"��õ����齣Ц����������� " + MONEY_D->money_str(10000000) + "��\n"NOR);
     tell_object(me, HIM"��õ����齣Ц��������ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR);    
     me->add("ggs/left_time",1080000);
	 tell_object(me, HIR"��õ����齣Ц��������ף�����������൱�൱����˫������ֵʱ�䣡��pk���Ͻ��һ���\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
		else
                me->add_condition("db_exp", 10000);

     CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ�ݷ���Ԫ�����\n"NOR);
    return 1;
}
int ask_qingming()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
    if( me->query("liwu/qingming")) 
       {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
       }


   if( me->query("combat_exp") < 150000 ) 
       {
          command("say 150k����н��������ʵս���鲻�㣬����ץ��ʱ��ȥ�����ɣ�������5.1�ڣ����˾Ϳ������ˡ�");
          return 1;
       }

     command("say Ϊ�˼�����Щ��ȥ�����ȣ���ʦ��������ֵܽ��Ƿ��������");
	 command("say �����ֵܽ����ڼ����ͬʱҲ��ϴ�ĸ��棬����ɱ¾,�����ӷ�");
	 command("say ���У�ǰһ�׶�Ƶ�������������ײ�����Ĳ�����崻���һ�����貹����");
     command("say ��л����֧�֣�ϣ������Ŀ��ģ���ĳ��ã�");
     me->set("liwu/qingming",1);
     me->add("SJ_Credit",500);
     //me->add("balance", 10000000);
	 me->add("potential", 100000);
     tell_object(me, HIR"\n\n\n�ر��л��ЩΪЦ�������ṩ��������ң���������ɰ����ˣ�\n\n\n"NOR);
     tell_object(me, HIC"\n\n\nԶ��quest,����˶����չ˼��ˣ��ذ��Լ���\n\n\n"NOR);

     tell_object(me, HIG"��õ����齣Ц��������ף�������"+ HIR + chinese_number(500) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
	      tell_object(me, HIG"��õ����齣Ц��������ף�������"+ HIR + chinese_number(100000) + CYN +"�㡸"+HIG+"Ǳ��"+CYN+"����\n"NOR);

     //tell_object(me, HIG"��õ����齣Ц����������� " + MONEY_D->money_str(10000000) + "��\n"NOR);
     tell_object(me, HIM"��õ����齣Ц��������ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR);    
     me->add("ggs/left_time",1080000);
	 tell_object(me, HIR"��õ����齣Ц��������ף�����������൱�൱����˫������ֵʱ��,��pk���Ͻ��һ���\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
        me->apply_condition("db_exp", 10000);
	 else
        me->add_condition("db_exp", 10000);

     CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ������������ں�崻����������\n"NOR);
    return 1;
}
int ask_51()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
    if( me->query("liwu/1751")) 
    {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
    }


   if( me->query("combat_exp") < 150000 ) 
       {
          command("say ���ʵս���鲻��150k������ץ��ʱ��ȥ�����ɣ�������5.1�ڣ����˾Ϳ������ˡ�");
          return 1;
       }

    // command("say Ϊ�˼�����Щ��ȥ�����ȣ���ʦ��������ֵܽ��Ƿ��������");
	 command("say ����51�Ͷ��ڣ�");
	// command("say ���У�ǰһ�׶�Ƶ�������������ײ�����Ĳ�����崻���һ�����貹����");
     //command("say ��л����֧�֣�ϣ������Ŀ��ģ���ĳ��ã�");
     me->set("liwu/1751",1);
     me->add("SJ_Credit",1000);
	 me->add("potential",15000);
     //me->add("balance", 5000000);
	 //me->add("balance", 10000000);
     tell_object(me, HIR"\n\n\n�ر��л��ЩΪ�齣Ц������վ�ṩ��������ң���������ɰ����ˣ�\n\n\n"NOR);
     tell_object(me, HIC"\n\n\nԶ��quest,����˶����չ˼��ˣ����³������ذ��Լ����塣\n\n\n"NOR);

     tell_object(me, HIG"��õ����齣Ц��������ף�������"+ HIR + chinese_number(1000) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
     //tell_object(me, HIG"��õ����齣Ц����������� " + MONEY_D->money_str(5000000) + "��\n"NOR);
	 tell_object(me, HIG"��õ����齣Ц��������ף������� " +chinese_number(15000) + "Ǳ�ܣ�\n"NOR);
     tell_object(me, HIM"��õ����齣Ц��������ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR);    
 //    me->add("ggs/left_time",1080000);
	 tell_object(me, HIR"��õ����齣Ц��������ף�����������൱�൱����˫������ֵʱ��,��������3�죡��pk���Ͻ��һ���\n"NOR);    
	
	 if(!mapp(me->query_conditions_by_type("db_exp"))) 
                me->apply_condition("db_exp", 10000);
		else
                me->add_condition("db_exp", 10000);
	
     CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ�ݷ����Ͷ������\n"NOR);
    return 1;
}
//��������
int ask_chunjie()
{
  
   object me = this_player(); 
   if( me->query("liwu_2018") ) 
       {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
       }


   if( me->query("combat_exp") < 500000  ) 
   {
          command("say ���ʵս���鲻��500000������ץ��ʱ��ȥ�����ɣ����Ĺһ��ɣ����ĵ������¡�");
		  command("say ������ʵ�һ��������õ�����������ϵͳbug���õ����ͷ��ְɡ�");
          return 1;
   }

     command("wink");

     command("say ����ʵս�������ڵ�500k�ˣ��治����ѽ��");
     command("say Ϊ������齣Ц������վ2018����������ףԸ�����ֵܽ�������ʵ�������������³ɣ�"HBYEL+HIR"��������"NOR+HBRED+HIW"�󼪴�����"NOR);
	 command("say ����");
	 command("say �ڣ�");
	 command("say �죡");
	 command("say �֣�");

     command("say Զ��quest,������ˣ��������壬����������");
     me->set("liwu_2018",1);
     me->add("SJ_Credit",1888);
     me->add("balance", 10000000);
  //   me->add("potential", 500000);

     tell_object(me, HIG"��õ���Ц��������ʦ�ǵ�����ף�������"+ HIR + chinese_number(1888) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
     tell_object(me, HIC"��õ���Ц��������ʦ�ǵ�����ף������� " + MONEY_D->money_str(10000000) + "��\n"NOR);
     tell_object(me, HIM"��õ���Ц��������ʦ�ǵ�����ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR); 

     tell_object(me, HIY"Ϊ����������������ʵ�ݣ��ؾ����ӳ�Ϧ�տ�ʼ��ֱ������ʮ��֮�䣬���ֻҪ·����������·�ڣ����ɻ����ѵ�˫�����飡\n"NOR);
	 tell_object(me, HIG"��õ���Ц��������ʦ�ǵĵ�һ������ף��������һ����\n"NOR);
	// tell_object(me, HIR"�мɣ��мɣ�����doubleʱ���������������ʮ������12�㣡\n"NOR); 
	// tell_object(me, HIR"���ŵ��̱��У���ң�\n"NOR); 
	// tell_object(me, HIY"���⣬���ŵ������ر��䣬������أ��������漴���������ȫƾ��������ʹȻ����\n"NOR);
//	 me->add("ggs/left_time",1080000);
     tell_object(me, HIR"��õ���Ц��������ʦ�ǵ�����ף�����������൱�൱����˫����������ʱ�䣡\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
	 else
                me->add_condition("db_exp", 10000);
	 /**/
    CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ�ݷ���2018�괺�����\n"NOR);
    return 1;
}
int ask_yuanxiao()
{
  
   object me = this_player(); 
   if( me->query("liwu/yuanxiao") ) 
       {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
       }


   if( me->query("combat_exp") < 160000  ) 
   {
          command("say ���ʵս���鲻��160000������ץ��ʱ��ȥ�����ɣ����Ĺһ��ɣ����ĵ������¡�");
		  command("say ������ʵ�һ��������õ�����������ϵͳbug���õ����ͷ��ְɡ�");
          return 1;
   }

     command("wink");

     command("say ����ʵս�������ڵ�160k�ˣ��治����ѽ��");
     command("say Ϊ������齣Ц������վ2015��������ʮ��Ԫ����������ףԸ�����ֵܽ�������ʵ������������Բ����");
	
     command("say ��л����֧�֣�ϣ������Ŀ��ģ���ĳ��ã�");
     me->set("liwu/yuanxiao",1);
     me->add("SJ_Credit",500);
     //me->add("balance", 10000000);
     //me->add("potential", 500000);

     tell_object(me, HIG"��õ���Ц��������ʦ�ǵ�����ף�������"+ HIR + chinese_number(500) + CYN +"����"+HIG+"ͨ��"+CYN+"����\n"NOR);
    // tell_object(me, HIC"��õ���Ц��������ʦ�ǵ�����ף������� " + MONEY_D->money_str(10000000) + "��\n"NOR);
  //   tell_object(me, HIM"��õ���Ц��������ʦ�ǵ�����ף�����������൱�൱���Ĺ������ʱ�䣡\n"NOR); 
	// tell_object(me, HIG"��õ���Ц��������ʦ�ǵ�����ף�������"+ HIR + chinese_number(500000) + CYN +"�㡸"+HIG+"Ǳ��"+CYN+"����\n"NOR);
     //tell_object(me, HIY"Ϊ����������������ʵ�ݣ��ؾ����ӳ�Ϧ�տ�ʼ��ֱ������ʮ��֮�䣬���ֻҪ·����������·�ڣ����ɻ����ѵ�˫�����飡\n"NOR);
	 tell_object(me, HIR"��õ���Ц��������ʦ�ǵ�ף�������һ����˫�����exp״̬��\n"NOR);
	 tell_object(me, HIR"�мɣ��мɣ���Ҫ��ˣ��Ŭ���һ���\n"NOR); 
	// tell_object(me, HIR"���ŵ��̱��У���ң�\n"NOR); 
	// tell_object(me, HIY"���⣬���ŵ������ر��䣬������أ��������漴���������ȫƾ��������ʹȻ����\n"NOR);
	// me->add("ggs/left_time",1080000);
 /*    tell_object(me, HIR"��õ���Ц��������ʦ�ǵ�����ף�����������൱�൱����˫����������ʱ�䣡\n"NOR);    */
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
	 else
                me->add_condition("db_exp", 10000);
	
    CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ�ݷ������\n"NOR);
    return 1;
}
int ask_nianka()
{
	//object vipcard;
	object me = this_player();
	if (me->query("buyvip"))
	{
		command("say ���Ѿ��������ˣ������꿨ô��\n");
		return 1;
	}
	if (me->query("combat_exp")<165000)
	{
		command("say ��ľ���ֵ����165k����Ѳ�Ǻ��������ȡ�꿨\n");
		return 1;
	}
	if (me->query("givevipcard")>1)
	{
		command("kick "+me->query("id"));
		command("say ����˵�˲�Ҫ��㶪��������ʼ������,�������ˣ�");
		return 1;
	}
	if (me->query("y-card-vip") && me->query("vip/vip_time"))
	{
		command("say �Բ������Ѿ����꿨����ˣ��벻Ҫ����ʦ����Ц��\n");
		//command("say ������ʣ��ʱ��Ϊ");
		return 1;
	}
	command("say �ԣ��꿨�쵽���ˣ��ٸ���һ�ţ��úùҡ�");
	command("say ���鲢�����Ǳ���Ϸ�ĺ���˼�롣");
	command("say Ϊ��ά�������ƽ��Ҫ�ú����ſ���");
	command("say ���ſ�Ҫ����ʹ�ã������ⶪ����");


	me->set("registered", 3);    
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());       

	me->add("vip/vip_time",365*24*3600);
	me->add("SJ_Credit",3000);
//	me->add("balance",20000000);
	me->set("y-card-vip",1);
	write(HIY"\n�㽫"HIW"�����ֵ��"NOR+HIY"���齣�Զ��տ����һˢ\n"NOR);
	
    write(HIY"\����齣ͨ����������Ǫ����\n"NOR);
 //   write(HIY"\n������д�������˷�ǧ����\n"NOR);
	///write(HIW"\n�齣�Զ�ϵͳΪ������������ʮ����Ĺ��VIP��Ŀǰ�ȼ�Ϊ"HIR"��"HIW",������"HIB"time"HIW"�鿴����л�Ķ��齣��֧�֡�\n"NOR);
	//degree();
	//new("d/wizard/npc/vipcard")->move(me);
	//me->add("givevipcard",1);
	CHANNEL_D->do_channel(this_object(), "sj", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ��"HIR"����꿨"HIC"���\n"NOR);

	return 1;
	
}
int ask_yueka()
{
	//object vipcard;
	object me = this_player();
	if (time()-me->query("vip/vip_time")<0)
	{
		//me->delete("m-card-vip");
		write(HIC"�������Ѿ���ȡ���¿�����ˡ�\n"NOR);
		return 1;
	}

	if (me->query("m-card-vip"))
	{
		//me->delete("m-card-vip");
		write(HIC"ע�⣬���Ѿ����¿�����ˡ�\n"NOR);
		return 1;
	}
	if (me->query("y-card-vip")||me->query("buyvip"))
	{
		write(HIC"ע�⣬��Ϊ�����Ѿ��ǹ���ˣ����������¿���\n"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if (me->query("give_mcard")>24)
	{
		command("kick "+me->query("id"));
		command("say ����˵�˲�Ҫ��㶪��������ʼ������,�������ˣ�");
		return 1;
	}

	command("say �ԣ��¿��쵽���ˣ��ٸ���һ�ţ��úùң����˷ѣ�ֻ��12�λ��ᡣ");
	command("say ���鲢�����Ǳ���Ϸ�ĺ���˼�롣");
	command("say Ϊ��ά�������ƽ��Ҫ�ú����ſ���");
	command("say ���ſ�Ҫ����ʹ�ã������ⶪ����");

	//new("clone/spec/bak/vipcard-m")->move(me);
	//me->add("give_mcard",1);
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());                                       ;
	me->add("vip/vip_time",30*24*3600);
	//me->add("balance",120000);
	me->add("SJ_Credit",100);
	me->set("m-card-vip",1);
	write(HIY"\n�㽫"HIW"�����ֵ��"NOR+HIY"���齣�Զ��տ����һˢ\n"NOR);
	CHANNEL_D->do_channel(this_object(), "sj", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ��"HIR"����¿�"HIC"���\n"NOR);

	return 1;
	
}

int ask_quanfa()
{      
       int i ;
       object me = this_player();
       i = me->query("max_pot",1) -100;

		if(i > 250 ) i= 250;
		if(me->query("askwiz_cuff") <4 ){

         if( me->query_skill("yeqiu-quan",1)< 250 )  me->set_skill("yeqiu-quan", i);
         if( me->query_skill("cuff",1) <250 )        me->set_skill("cuff", i);
    
          me->add("askwiz_cuff",1);
          command("say �ðɣ��ҿ��Խ���һ�����������书��");
          command("say �����ֻ�������顣���Ҫ����ϸ�ˡ���ʱ��ѧ����ɾͲ�Ҫ��������");
            
             return 1;
           }
 else {
                  command("say ���书�Ѿ��ܸ��ˡ��ҿɽ̲�����ʲô������");  
                  return 1; 
                  }
      
        
}

int ask_jiangli()
{
  
    object me = this_player(); 
  
   if( me->query("5m_jiangli") ) 
       {
          command("say �㲻���Ѿ�����ˣ�");
          return 1;
       }


   if( me->query("combat_exp") < 5000000  ) 
       {
          command("say ���ʵս���鲻��5M������ץ��ʱ��ȥ�����ɡ�");
          return 1;
       }

     command("ah");
     command("say ��ϲ��������������ֵ����У�");
     command("say �����������һ�ζ���İ����ˣ��Ժ��Ҫ�����Լ��ܶ��ˣ�");
     me->set("5m_jiangli",1);
     me->add("SJ_Credit",2000);
     me->add("balance", 20000000);

     me->add("relife/gifts/now",  2);  
     me->add("relife/gifts/total",  2);  
     me->add("imbue_reward",10);


     tell_object(me, HIC"��õ��������ף�������"+ HIR + chinese_number(2000) + HIC +"����"+HIG+"�齣ͨ��"+HIC+"���� " + MONEY_D->money_str(20000000) + "��\n"NOR);
     tell_object(me, HBBLU"��õ��������ף����������������ɷ���Ĳ����츳��������ʹ��addgiftָ����䣡\n"NOR);  
     tell_object(me, HBBLU"����ʮ�ζ���Ĵ�����ᣡ\n"NOR);   
     me->add("ggs/left_time",1080000);


    tell_object(me, HBBLU"�츳ϵͳ��ʼ��Ч������һ�ε�½��ʼ���㽫��ö���Ĺ���������ʵս�н�����������Ч����\n"NOR);  
 
     CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ӻ���ҵ���ʦ�������һ��"HIR"���ֽ���"HIC"���\n"NOR);
     return 1;     

}


int ask_vip()
{      
     object me = this_player(); 
  
   if( !me->query("buyvip") ) 
       {
          command("say �Բ�����Ŀǰ������ʹ������ҵ��");
          return 1;
       }


   if( me->query("combat_exp")- me->query("buyvip/combat_exp")<1000000  && me->query("buyvip/newbie") ) 
       {
          command("say �Բ���ÿ��1M�ſ���ʹ��һ�α���ҵ��");
          return 1;
       }

     command("say ��ӭʹ��Ц�������齣VIP����ҵ��");
     
     command("say ����VIP���ÿ��1M������ȡ1000ͨ����1000���ƽ�Ķ��⽱����");
     
     command("say ͬʱVIP��ҿ�����0-6M�ڼ���Ѳ����似��Σ�����ϧʹ�ã�");
     
     me->set("buyvip/combat_exp",me->query("combat_exp"));
     me->add("SJ_Credit",1000);
     me->add("balance", 10000000);
     me->add("imbue_reward",10);
     me->set("vip/vip_time",time());
     me->add("vip/vip_time",365*24*3600);
     me->set("vip/vip_start_time",time());  
me->set("registered",3);
     me->set("buyvip/newbie",1);
     me->set("y-card-vip",1);
 if(me->query("combat_exp")<6000000 )   command("fullskills "+me->query("id"));

     tell_object(me, HIC"��ʹ����VIP����������ȡ��"+ HIR + chinese_number(1000) + HIC +"����"+HIG+"�齣ͨ��"+HIC+"���� " + MONEY_D->money_str(10000000) + "��\n"NOR);
 if(me->query("combat_exp")<5000000 )     tell_object(me, HBBLU"���Ѿ�ʹ����һ��Fullskillsָ�\n"NOR);  
     tell_object(me, HBBLU"����ʮ�ζ����?�����ᣡ\n"NOR);   
     tell_object(me, HBBLU"���VIPʹ?������Զ�����Ϊһ�꣡\n"NOR);   
//      CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "������ҵ���ʦ��������һ��"HIR"VIPר��ҵ��"HIC",����˲������\n"NOR)
//      CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "������ҵ���ʦ��������һ��"HIR"VIPר��ҵ��"HIC",����˲������\n"NOR);
     return 1;     

        
}


