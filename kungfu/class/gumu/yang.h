// yangguo.h 杨过 谜题设计

//黯然掌谜题
//去密林中救治史家兄弟，
//寻找灵狐，瑛姑出现，提出要求寻找周伯通
//百花谷寻找周伯通,开始打架,现场观悟



int thinking(object me)
{
  int i,j,s,total,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(20);
    j = 25;
    if(me->query("m-card-vip")) j =  23;
    if(me->query("y-card-vip")) j =  20;
    if(me->query("buyvip"))     j =  17;
	//古墓派的有偏爱
	if (me->query("family/family_name")=="古墓派")
	     s=random(j-3);
	else s= random(j);
 
  
  total=random(me->query("int")+me->query("str")+me->query("con")+me->query("dex"));
  t=random(me->query("int"));
  me->set("quest/xtjf/time",time());
  
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟玄铁剑法时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_xtjf")<(10+random(10)))
   {  
	  me->add_temp("canwu_xtjf",1);
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

	  //remove_call_out("thinking");

	  call_out("thinking",3+random(3), me);

   } 
   else if (i>28
			&& s<2
			&& total>120
			&& t>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了杨过传授的玄铁剑法的口诀奥秘！”\n"NOR,me); 
         log_file("quest/xtjf", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟玄铁剑法绝技的奥秘，当前幸运值：%d,当前随机值s：%d,当前经验：%d,当前总属性：%d,当前悟性：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xtjf/fail"),
		 i,
		 s,
         me->query("combat_exp"),
		 total,
		 t));

		 me->set("quest/xtjf/time",time());
		 me->set("quest/xtjf/pass",1);
		 me->delete_temp("canwu_xtjf");
		 me->delete_temp("xtjf");

		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一声，自言自语地说道：“看来这绝世的玄铁剑法真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟玄铁剑法绝技解密失败！\n"NOR,me); 
         log_file("quest/xtjf", sprintf("%s(%s) 失败！第%d次失败参悟玄铁剑法，当前幸运值：%d,当前随机值s：%d,当前经验：%d。,当前总属性：%d,当前悟性：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xtjf/fail",1),
		 i,
		 s,
         me->query("combat_exp"),
		 total,
		 t));        
		 me->add("quest/xtjf/fail",1);
		 me->set("quest/xtjf/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_xtjf");
		 me->delete_temp("xtjf");
		 return 1;
   }

}

int anran_think(object me)
{
  int i,j,s,total,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(20);
    j = 25;
    if(me->query("m-card-vip")) j =  23;
    if(me->query("y-card-vip")) j =  20;
    if(me->query("buyvip"))     j =  17;
	//古墓派的有偏爱
	if (me->query("family/family_name")=="古墓派")
	     s=random(j-3);
	else s= random(j);
 
  
  total=random(me->query("int")+me->query("str")+me->query("con")+me->query("dex"));
  t=random(me->query("str"));
  me->set("quest/anran/time",time());
 
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟玄铁剑法时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_anran")<(10+random(10)))
   {  
	  me->add_temp("canwu_anran",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听杨过的讲述，将杨过所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
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

	//  remove_call_out("anran_think");
	  call_out("anran_think",3+random(3), me);

   } 
   else if (i>28
			&& s<2
			&& total>120
			&& t>40
			&& me->query("kar")<31)
 	{ 
         me->delete_temp("canwu_anran");
         me->start_busy(3);     
         message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了杨过传授的黯然销魂掌的口诀奥秘！”\n"NOR,me); 
		 command("chat 恭喜"+me->query("name")+"领悟黯然销魂掌绝技！\n");
		 command("chat 黯然销魂掌将重现江湖！");
         log_file("quest/anranzhang", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟黯然掌绝技的奥秘，当前幸运值：%d,当前随机值s：%d,当前经验：%d,当前总属性：%d,当前悟性：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/anran/fail"),
		 i,
		 s,
         me->query("combat_exp"),
		 total,
		 t));

		 me->set("quest/anran/time",time());
		 me->set("quest/anran/pass",1);
		 me->set_skill("anran-zhang",11);
		 message_vision(HIC"\n你的「黯然消魂掌」进步了！”\n"NOR,me); 
		 me->delete_temp("canwu_anran");
		 me->delete_temp("anran");
		 me->start_busy();
		 return 1;
     }
	  else {
	     message_vision(HIG"\n\n$N长叹一声，自言自语地说道：“看来这绝世的黯然掌法真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n\n参悟黯然销魂掌绝技解密失败！\n"NOR,me); 
         log_file("quest/anranzhang", sprintf("%s(%s) 失败！第%d次失败参悟黯然掌法，当前幸运值：%d,当前随机值s：%d,当前经验：%d。,当前总属性：%d,当前悟性：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/anran/fail",1),
		 i,
		 s,
         me->query("combat_exp"),
		 total,
		 t));        
		 me->add("quest/anran/fail",1);
		 me->set("quest/anran/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_anran");
		 me->delete_temp("anran");
		 return 1;
   }

}