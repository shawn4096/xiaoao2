// hant.h 洪安通
//化骨绝技
//#include "ansi.h"

int do_huagu()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(1);
	if (me->query("family/family_name") != "神龙教" ){
		command("say 你不是我神龙教中人士来此作甚？\n");
		return 1;
	}
	if (me->query("family/generation")>2)
	{
		command("say 你非二代弟子，来此作甚？？\n");
		return 1;
	}
	if (me->query_skill("huagu-mianzhang",1)<450)
	{
		command("say 你的化骨绵掌不足450，来了也学不了？\n");
		return 1;
	}    
	if (me->query("quest/sld/hgmz/pass")){
		command("say 你已经开了这个谜题还来此作甚？？\n");        	
		return 1;				
	}
	if (me->query("gender")=="女性"){
		command("say 唉！化骨绵掌这功夫，我看女娃娃就算了？？\n");        	
		return 1;				
	}
	if (time()-me->query("quest/sld/hgmz/time")<86400){
		command("say 你也太勤快点了耶？？\n");        	
		return 1;				
	}
	if (me->is_busy())
	{
		command("say 你也手忙脚乱在那作甚？？\n");        	
		return 1;			
	}

		    command("say 大神龙教一切根基全在这蛇岛之上，而化骨绵掌的精要就是毒。\n");
		    command("say 化骨绵掌讲究的不是快，不是猛，其要点在于狠，辣。\n");
			command("say 看你小子一副心狠手辣的模样，到适合这门神功的传承。\n\n\n");
			me->set_temp("hgmz/askhong",1);
			if (random(me->query("kar"))>25)
			{
				command("say 今天我正好心情高兴，乖徒儿，来来！我就把这化骨绵掌的精要说与你听听。你要听好了！\n");
				message_vision(HIR"\n\n$N恭恭敬敬地向师傅洪安通请教关于化骨绵掌的绝技。\n"NOR,me);
				me->start_busy(999);
				remove_call_out("thinking");
				call_out("thinking",1,me);
				me->delete_temp("hmgz/askhongok",1);
				return 1;

			}else {
				
				command("say 今天我心情不好，你给我站远点！\n");
				command("say 天天守着个小美人不能碰，真窝火！\n");

				message_vision(HIR"\n\n$N恭恭敬敬地向师傅洪安通请教关于化骨绵掌的绝技。\n"NOR,me);
				
				me->add_temp("hgmz/askhong",1);
				if (me->query_temp("hgmz/askhong")>4)
				{
					command("say 别聒噪！\n");
					command("shout "+me->query("name")+"这个混小子老是来烦我，别逼我出手！\n");
					message_vision(HIR"\n\n洪安通不明所以，突然间勃然大怒，一脚将$N踢出门外。\n"NOR,me);
					me->move("d/sld/ht");
					me->add_busy(1);
				}

				return 1;
			}
}
//化骨绵掌 化骨
int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
 
  j = 25;
  if(me->query("m-card-vip")) j =  22;
  if(me->query("y-card-vip")) j =  20;
  if(me->query("buyvip"))     j =  17;
  j=random(j);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟化骨绵掌时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_huagu")<(30+random(10)))
   {  
	  me->add_temp("canwu_huagu",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>26
			&& j<3
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了洪教主所传授的化骨绵掌的奥秘豁然贯通！”\n"NOR,me); 
         log_file("quest/huagumianzhang", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟化骨绝技的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/hgmz/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/hgmz/time",time());
		 me->set("quest/sld/hgmz/pass",1);
		 me->delete_temp("canwu_huagu");
		 me->delete_temp("hgmz");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟化骨绵掌绝技解密失败！\n"NOR,me); 
         log_file("quest/huagumianzhang", sprintf("%s(%s) 失败！第%d次失败参悟化骨绵掌，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/hgmz/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/hgmz/fail",1);
		 me->set("quest/sld/hgmz/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_huagu");
		 me->delete_temp("hgmz");
		 return 1;
   }

}
//毒龙大法绝世

int do_dldf()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(1);
	if (me->query("family/family_name") != "神龙教" ){
		command("say 你不是我神龙教中人士来此作甚？\n");
		return 1;
	}
	if (me->query_skill("dulong-dafa",1)<500 ){
		command("say 你的毒龙大法不足500，来此作甚？\n");
		return 1;
	}
	if (!me->query("quest/sld/dldf/start")){
		command("say 你为我大神龙岛曾经做错过什么贡献？\n");
		command("sigh ");
		command("say 只有多做海战任务，为我大神龙立下汗马功劳，才能获得我的真传！\n");
		return 1;
	}
	if (me->query("family/generation")>2)
	{
		command("say 你非二代弟子，来此作甚？？\n");
		return 1;
	}
	if (me->query_skill("dulong-dafa",1)<450)
	{
		command("say 你的毒龙大法不足450，来了也学不了？\n");
		return 1;
	}
    if (me->query("quest/sld/dldf/pass")){
		command("say 你已经开了这个谜题还来此作甚？？\n");
		me->set("title",HIG"神龙教"+HIB"毒龙大法传人"NOR);

		return 1;				
	}
    if (me->query("con")<40){
		command("say 你的先天根骨不足40，抵抗不了毒气攻心？？\n");        	
		return 1;				
	}
//	if (me->is_busy())
	//{
		//command("say 你也手忙脚乱在那作甚？？\n");        	
		//return 1;			
//	}

	if (time()-me->query("quest/sld/dldf/time")<86400){
		command("say 你也太勤快点了耶？？\n");        	
		return 1;				
	}
		    command("say 大神龙教一切根基全在这毒龙大法的内功之上，可以说这是我神龙教的根本。\n");
		    command("say 毒龙大法需要以毒养功，借功练毒，最终二者达到融会贯通。\n");
			command("say 看你一副心狠手辣的模样，到适合这门神功的传承，不过要切记，这毒和内功处理也比较危险。\n");
			command("say 稍有不慎可能毒发身亡，切记切记。\n\n\n");

			me->set_temp("dldf/askhong",1);
			
			if (random(me->query("kar"))>25)
			{
				command("say 今天我正好心情高兴，乖徒儿，来来！我就把这毒龙大法的精要说与你听听。你要听好了！\n");
				message_vision(HIC"\n\n$N恭恭敬敬地向师傅洪安通请教关于毒龙大法的绝技。\n"NOR,me);
				me->start_busy(999);
				remove_call_out("thinking_dldf");
				call_out("thinking_dldf",1,me);
				me->delete_temp("dldf/askhong",1);
				return 1;

			}else {
				
				command("say 今天我心情不好，你给我站远点！\n");
				command("say 天天守着个小美人不能碰，真窝火！\n");

				message_vision(HIR"\n\n$N恭恭敬敬地向师傅洪安通请教关于毒龙大法的绝技。\n"NOR,me);
				
				me->add_temp("hgmz/askhong",1);
				if (me->query_temp("hgmz/askhong")>5)
				{
					command("say 别聒噪！\n");
					command("shout "+me->query("name")+"这个混小子老是来烦我，别逼我出手！\n");
					message_vision(HIR"\n\n洪安通不明所以，突然间勃然大怒，一脚将$N踢出门外。\n"NOR,me);
					me->move("d/sld/ht");
					me->start_busy(1);
				}

				return 1;
			}
}

int thinking_dldf(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  me->set("quest/sld/dldf/time",time());
  
  j = 25;
  if(me->query("m-card-vip")) j =  23;
  if(me->query("y-card-vip")) j =  20;
  if(me->query("buyvip"))     j =  17;
  j=random(j);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟毒龙大法时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_dldf")<(10+random(10)))
   {  
	  me->add_temp("canwu_dldf",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking_dldf");
	  call_out("thinking_dldf",3+random(3), me);

   } 
   else if (i>27
			&& j<2
	   		&& random(me->query("con"))>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了洪教主所传授的毒龙大法的奥秘豁然贯通！”\n"NOR,me); 
		 message_vision(HIG"\n恭喜！！，$N千辛万苦，终于得偿所愿，解开毒龙大法的终极谜题！”\n"NOR,me); 

         log_file("quest/dldf", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟毒龙大法的奥秘，当前随机幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/dldf/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/dldf/time",time());
		 me->set("quest/sld/dldf/pass",1);
		 me->start_busy(1);
		 me->set("title",HIG"神龙教"+HIR"毒龙大法传人"NOR);
		 me->delete_temp("canwu_dldf");
		 me->delete_temp("dldf");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟毒龙大法没能领悟到毒和气融合的契机,导致蛇毒发作！\n"NOR,me); 
		 me->apply_condition("snake_poison",1);
		 message_vision(HIY"\n参悟毒龙大法绝技解密失败！\n"NOR,me); 
         log_file("quest/dldf", sprintf("%s(%s) 失败！第%d次失败参悟毒龙大法绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/dldf/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/dldf/fail",1);
		 me->set("quest/sld/dldf/time",time());
		 me->start_busy(1);
		 me->delete_temp("canwu_dldf");
		 me->delete_temp("dldf");
		 return 1;
   }

}

/**/
//毒龙大法之毒龙绝技


string do_dulong()
{
	object me,ob;
	int i,j;
	me=this_player();
	if (!me->query("quest/sld/dldf/dulong/start"))
	{
		command("say 你尚未了解神龙灵动驱使之理，来了也白搭！");
		return "哼\n";
	}
	if (!me->query_temp("quest/sld/dulong/asksu"))
	{
		command("say 这件事跟我有关系么？！");
		return "哼\n";
	}

	if (me->query_skill("qusheshu",1)<200)
	{
		command("say 驱蛇术需要达到200大飞阶段方可修习！\n");
		return "";
	}
	if (me->query_skill("force",1)<450)
	{
		command("say 基本内功达到450大飞阶段方可修习！\n");
		return "";
	}
	if (me->query("family/family_name")!="神龙教")
	{
		command("say 你并非神龙教弟子！\n");
		return "";
	}
	if (time()-me->query("quest/sld/dldf/dulong/time")<86400)
	{
		command("say 你来的太频繁了！\n");
		return "";
	}
	if (me->query("quest/sld/dldf/dulong/pass"))
	{
		command("say 你已经解开这个谜题了！\n");
		return "";
	}
	
	command("consider ");
	command("sigh "+me->query("id"));
	command("say 既然是夫人让你来找我，我就跟你说下吧！\n");
	message_vision(HIY"洪安通对$N说，“你很不错，竟然能在训蛇过程中有这么多关于神龙的领悟，看来是可造之材！”\n"NOR,me);

	command("say 我神龙岛最大的特色之一就是对于各种毒蛇的研究。\n");
	command("say 后来穷我一生精力我才发现，神龙也是可以控制，倘若配合毒龙大法，威力大增。\n");
	command("say 可以在对战过程中将宠物放出来，令对方防不胜防。\n");
	command("say 当然你可以用神龙来替你抵挡一招救命招式，但神龙也就会死掉，你需要重新再驯养一条！\n");
	command("say 你若感兴趣我就将这门绝技传授于你！\n");
	

	
	if( !objectp(ob=me->query_temp("sld/snake")) 
		||!present("jin she",me))
		return "你需要先驯养一条宠物蛇方可请教。\n";
	  
	if (me->is_busy())
	{
	  command("say 你正在忙碌中!\n");
	  return "";
	}
	me->start_busy(20);
	command("say 事先声明，你向我请教需要扣除你的门派贡献值每次200点，如果不够你没资格请教我。\n\n\n\n");

	if (me->query("party/gongji")<100)
	{
		command("say 你的门派功绩不够\n");
		return "";
	}
	command("say 好吧，既然你如此努力，我就告诉你其中诀窍。\n");
    command("whisper "+me->query("id"));
	me->add("party/gongji",-100);
	
	i = 25;
		if(me->query("m-card-vip")) i =  22;
		if(me->query("y-card-vip")) i =  20;
		if(me->query("buyvip"))     i =  17;
		i=random(i);
		j=random(me->query("kar"));
		command("say 你听懂了么。\n");
		command("pat "+me->query("id"));
		if( i<3
			&& me->query("kar")<31
			&& random(me->query_int(1))>35
			&& j > 27 ) 
		{
			tell_object(me,HIC"\n你听了的洪安通的亲自指点，联想起早期自己驯蛇过程中的种种心得，两下彼此印照，颇有心得。\n"NOR);
			tell_object(me,HIG"\n你按照洪安通的指点，将以毒龙大法运使自己所驯养的神龙，无不如意。\n"NOR);
			tell_object(me,HIB"\n你发现那条神龙在毒龙诀运使之下，灵动异常！\n"NOR);
			tell_object(me,HIY"\n你历经千辛万苦，终于练成毒龙大法毒龙绝技！\n"NOR);

			me->set("quest/sld/dldf/dulong/pass",1);
			log_file("quest/slddulong", sprintf("%8s(%8s) 失败%d次后，学到毒龙大法毒龙诀绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|后天根骨：%d。\n",
				me->name(1),me->query("id"), me->query("quest/sld/dldf/dulong/fail"),i,j,me->query("kar"),me->query_con(1)) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "恭喜解密毒龙诀绝技成功!\n";
			
		}	
	   else
		{
			log_file("quest/slddulong", sprintf("%8s(%8s) 解密毒龙诀绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/sld/dldf/dulong/fail"),i,j,me->query("kar"),me->query_con(1)) );
			
			tell_object(me,HIY"你听了苏荃的指点，可是对毒龙诀绝技的奥妙全然不得要领。\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/sld/dldf/dulong/fail",1);
			me->set("quest/sld/dldf/dulong/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			me->start_busy(2);
			return "非常遗憾解密毒龙诀绝技失败"+me->query("quest/sld/dldf/dulong/fail")+"次。\n";
		}

	
}