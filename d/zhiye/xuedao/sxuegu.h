// attacker.h for hs job
#include <ansi.h>
int do_move(string arg);

void init()
{
	object me;
	me=this_player();
	if (!me->query("quest/xd/jglts/jingang/pass"))
	{	
		tell_object(this_player(),WHT"\n闷在雪层中，呼吸有些困难.\n"NOR);
		
	}else tell_object(this_player(),WHT"\n闷在雪层中，金刚炼体术已然大成，呼吸丝毫不觉得困难。\n"NOR);
	
	if (this_player()->query_temp("xd/xgjz"))
	{
		tell_object(this_player(),YEL"\n注意：雪中隐藏了高手，绝对不能待在一个固定地方。\n"
	+"所以需要不断前后左右（east,south,north,west）移动（move）来寻找敌人并将之杀死。\n"NOR);
	}
	if (this_player()->query("killer"))
	{
		tell_object(this_player(),"\n注意：凶手不能进入此地。\n");
		this_player()->move("d/");

	}
	if (this_object()->query("xueceng")>2 && !me->query("quest/xd/jglts/jingang/pass"))
	{
		tell_object(this_player(),YEL"\n此地空气极为稀薄，你觉得有些气闷。\n"NOR);
		if (!this_player()->query_condition("xuegu_bieqi"))
		{
			this_player()->apply_condition("xuegu_bieqi",5);
		}
	}
	add_action("do_tanting","tanting");
	add_action("do_tanting","ting");
	add_action("do_move","move");
	add_action("do_lianti","lianti");
}

int do_move(string arg)
{
	object me;
	int i;
	me=this_player();
	i=this_object()->query("xueceng");
	
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中！\n");
	}
	if (!arg)
	{
		return notify_fail("你要向那个方向移动?\n");
	}
	switch (arg)
	{
		case "east" :
			tell_object(me,YEL"你双手连刨带挖，快速向东移动了数尺!\n"NOR);
			me->add_temp("xuegu/east",1);
			me->move(__DIR__"sxuegu"+i+"1");
			me->start_busy(1);
			break;
		case "west" :
			tell_object(me,WHT"你双手连刨带挖，快速向西移动了数尺!\n"NOR);
			me->add_temp("xuegu/west",1);
			me->move(__DIR__"sxuegu"+i+"2");
			me->start_busy(1);

			break;
		case "north" :
			tell_object(me,CYN"你双手连刨带挖，快速向北移动了数尺!\n"NOR);
			me->add_temp("xuegu/north",1);
			me->move(__DIR__"sxuegu"+i+"3");
			me->start_busy(1);

			break;
		case "south" :
			tell_object(me,MAG"你双手连刨带挖，快速向南移动了数尺!\n"NOR);
			me->add_temp("xuegu/south",1);
			me->move(__DIR__"sxuegu"+i+"4");
			me->start_busy(1);

			break;	
		
		case "up" :  //每次上行或下行都将清零临时部署
			
			if (this_object()->query("zuan"))
			{
				tell_object(me,HIW"你发现此处雪中上面有所空隙，似乎有人向上爬过的雪洞!\n"NOR);
				tell_object(me,HIW"寻着这条现成的上下雪道，向上爬去!\n"NOR);
				if (this_object()->query("xueceng")==1)
				{
					//me->delete_temp("xd");
					//me->delete_temp("xuegu");
					me->move("d/xuedao/xuegu1");	
					tell_object(me,HIC"你爬出了雪谷，清新空气扑面而来，贪婪地吸了起来!\n"NOR);
					if (me->query_temp("xd/xgjz_job") && me->query_temp("xuegu"))
					{
						tell_object(me,HIR"经过雪谷激战，你已经杀了南方四大正派的掌门，可以考虑回去交差了：\n"NOR);
						//tell_object(me,HIR"你已经杀了：\m"NOR);
					}
				}
				if (this_object()->query("xueceng")==2)
					me->move("d/xuedao/sxuegu10");			

				if (this_object()->query("xueceng")==3)
					me->move("d/xuedao/sxuegu20");			
				if (this_object()->query("xueceng")==4)
					me->move("d/xuedao/sxuegu30");			
				//me->delete_temp("xuegu");
			}					
			else tell_object(me,HIR"用手向上扒了扒，雪甚厚且坚硬，发现根本无法上行!\n"NOR);	
			me->delete_temp("xuegu/north");
			me->delete_temp("xuegu/east");
			me->delete_temp("xuegu/west");
			me->delete_temp("xuegu/south");

			me->start_busy(1);
			break;	
		case "down" :
			if (this_object()->query("zuan"))
			{
				tell_object(me,HIW"你发现此处雪中上面有所空隙，似乎有人向下爬过的雪洞!\n"NOR);
				tell_object(me,HIW"寻着这条路径，向下爬去!\n"NOR);
				if (this_object()->query("xueceng")==1)
					me->move("d/xuedao/sxuegu20");	
				if (this_object()->query("xueceng")==2)
					me->move("d/xuedao/sxuegu30");			

				if (this_object()->query("xueceng")==3)
					me->move("d/xuedao/sxuegu40");			
				if (this_object()->query("xueceng")==4)
					tell_object(me,HIR"用手向下扒了扒，手指触到了坚硬的地面，无法再向下爬了!\n"NOR);
				//me->delete_temp("xuegu");
			}
			else tell_object(me,HIR"用手向下扒了扒，下面雪甚厚且异常坚硬，发现根本无法向下!\n"NOR);	
			me->delete_temp("xuegu/north");
			me->delete_temp("xuegu/east");
			me->delete_temp("xuegu/west");
			me->delete_temp("xuegu/south");

			me->start_busy(1);
			break;	

		default:
			tell_object(me,HIC"你双手连刨带挖，胡乱走了半天又回到了原地!\n"NOR);
			
			if (this_object()->query("xueceng")==1)
				me->move(__DIR__"sxuegu10");
			else if (this_object()->query("xueceng")==2)
				me->move(__DIR__"sxuegu20");
			else if (this_object()->query("xueceng")==3)
				me->move(__DIR__"sxuegu30");
			else if (this_object()->query("xueceng")==4)
				me->move(__DIR__"sxuegu40");
			else me->move(__DIR__"xuegu");
			//如果离开则清除临时标记
			me->delete_temp("xuegu/north");
			me->delete_temp("xuegu/east");
			me->delete_temp("xuegu/west");
			me->delete_temp("xuegu/south");
			
			break;
	}
	me->add_busy(1);
	return 1;
}

int do_tanting()
{	
	object me,ob;
	me=this_player();
	tell_object(me,me->query("name")+CYN"凝神倾听，仔细观察周围的动静!\n"NOR);
	
	if (!me->query_temp("xd/xgjz_job")) return notify_fail("你侧耳倾听，雪中万籁俱静无声！\n");
	
	
	
	if (random(me->query_temp("xuegu/north"))>=2
		&&random(me->query_temp("xuegu/east"))>=2
		&&random(me->query_temp("xuegu/west"))>=2
		&&me->query_temp("xd/xgjz_job")
		&&random(me->query_temp("xuegu/south"))>=2)
	{
		switch (query("xueceng"))
		{
			case 1:
				if (me->query_temp("xuegu/lutianshu")) break;
				
				message_vision(YEL"突然,$N听到前方雪中有一阵阵喘息的声音，似乎有人正在向这边移动过来!\n"NOR,me);
				message_vision(HIR"$N立即警觉，凝神备战，这时，只见前方的雪堆一阵鼓动，一个浑身是雪的人陡然出现在你面前!\n"NOR,me);
				
				ob=new("d/xuedao/npc/lutianshu");
				
				ob->set_name("陆天抒", ({ me->query("id")+"\'s lutianshu","lu" }));
				//ob->set("id",me->query("id")+"\'s lutianshu");
				ob->do_copy(me);
				ob->move(environment(me));
				ob->set_temp("target", me->query("id"));

				ob->kill_ob(me);
				
				me->set_temp("xuegu/lutianshu",1);
				break;
			case 2:
				if (me->query_temp("xuegu/huatiegan")) break;

				message_vision(HIG"突然,$N听到前方雪中有一阵阵喘息的声音，似乎有人正在向这边移动过来!\n"NOR,me);
				message_vision(HIR"$N立即警觉，凝神备战，这时，只见前方的雪堆一阵鼓动，一个浑身是雪的人陡然出现在你面前!\n"NOR,me);
				ob=new("d/xuedao/npc/huatiegan");
				//ob->set("id",me->query("id")+"\'s huatiegan");
				ob->set_name("花铁干", ({ me->query("id")+"\'s huatiegan", "hua" }));
				ob->do_copy(me);

				ob->move(environment(me));
				ob->set_temp("target", me->query("id"));
				ob->kill_ob(me);
				me->set_temp("xuegu/huatiegan",1);

				break;
			
			case 3:
				if (me->query_temp("xuegu/liuchengfeng")) break;
				message_vision(HIY"突然,$N听到前方雪中有一阵阵喘息的声音，似乎有人正在向这边移动过来!\n"NOR,me);
				message_vision(HIR"$N立即警觉，凝神备战，这时，只见前方的雪堆一阵鼓动，一个浑身是雪的人陡然出现在你面前!\n"NOR,me);
				ob=new("d/xuedao/npc/liuchengfeng");
				ob->set_name("刘承风", ({ me->query("id")+"\'s liuchengfeng","liu" }));
				//ob->set("id",me->query("id")+"\'s liuchengfeng");
				ob->do_copy(me);

				ob->move(environment(me));
				ob->set_temp("target", me->query("id"));
				
				ob->kill_ob(me);
				me->set_temp("xuegu/liuchengfeng",1);

				break;

			case 4:
				if (me->query_temp("xuegu/shuidai")) break;
				
				message_vision(HIY"突然,$N听到前方雪中有一阵阵喘息的声音，似乎有人正在向这边移动过来!\n"NOR,me);
				message_vision(HIR"$N立即警觉，凝神备战，这时，只见前方的雪堆一阵鼓动，一个浑身是雪的人陡然出现在你面前!\n"NOR,me);
				ob=new("d/xuedao/npc/shuidai");
				ob->set_name("水岱", ({ me->query("id")+"\'s shuidai", "shui" }));
				//ob->set("id",me->query("id")+"\'s shuidai");
				ob->do_copy(me);

				ob->move(environment(me));
				ob->set_temp("target", me->query("id"));
				
				ob->kill_ob(me);
				me->set_temp("xuegu/shuidai",1);
				break;

			default:
				me->move(__DIR__"xuegu");
			break;
		}
		//me->delete_temp("xuegu");
		tell_object(me,WHT"你双手连刨带挖，快速向西移动了数尺!\n"NOR);
	}
	me->start_busy(1);
	return 1;
}

//修炼金刚炼体术


int do_lianti()
{
	object me,weapon;
	me=this_player();
	if (!me) return 1;
	
	
	if (me->query_skill("xuedao-jing",1)<350)
	{

		return notify_fail("你血刀经不足350，怎么修炼也不得要领！\n");
	}
	if (me->query("family/family_name")!="血刀门")
	{
		return notify_fail("你不是血刀门弟子，来此消遣老祖我么？\n");
	}

	if (me->query("quest/xd/jglts/jingang/pass"))
	{
		
		return notify_fail("你已经解开了这个谜题，你无缘无故来找我作甚？？\n");
	}


	if (time()-me->query("quest/xd/jglts/jingang/time")<86400)
	{
		//command("say 你");
		return notify_fail( "你来的太频繁了，武功最忌讳心气浮躁？？\n");
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		return notify_fail( "血刀需要的是始终如一的忠诚弟子，你非嫡传，焉能传授你高级武功？？\n");
	}
	if (me->query_temp("quest/xd/jglts/jingang/lianti"))
	{
		return notify_fail("你正在炼体中!\n");

	}
	if (!me->query_temp("quest/xd/jglts/jingang/start"))
	{
		return notify_fail("你没有得到老祖的心法传授和指点，在雪堆中憋了了半天也不得要领！\n");
	}

	message_vision(HIY"$N运使老祖传授的运气法门，头朝下，将自己大半个身子埋在雪堆中，只余下双腿露在外面！\n"NOR,me);
	me->set_temp("quest/xd/jglts/jingang/lianti",1);
	me->start_busy(2);
	me->delete_temp("quest/xd/jglts");
	//remove_call_out("do_lianti");
	call_out("do_lianxi",1,me);
	return 1;
}

int do_lianxi(object me)
{
   int i,j,jobs; 
	if(!me) return 0;
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	

   jobs=(int)me->query("job_time/血刀打猎")+(int)me->query("job_time/血刀警戒");
   if(me->query_temp("canwu_lianti")<(10+random(10)))
   {  
	  me->add_temp("canwu_lianti",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你将自己头埋在雪中，屏住呼吸，顿时气血上涌.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n你仔细体味血刀经运转的技巧，虽然有些气闷，但并不难受。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你一时心气浮躁，真气堵塞胸口，强行将一口鲜血咽了下去！..\n"NOR);
			 me->add_temp("canwu_lianti",-3);
			break;
		case 3:
			tell_object(me,HIW"\n你头朝下，理顺真气奔走于奇经八脉，似乎有所心得.\n"NOR);
			me->add_temp("canwu_lianti",1);

			break;
		case 4:
			tell_object(me,CYN"\n你气血乱窜，此次炼体进入关键时期.\n"NOR);
			me->add_temp("canwu_lianti",-1);

			break;
		case 5:
			tell_object(me,MAG"\n你真气运转如意，顿觉气血充盈，本次修炼大有所获.\n"NOR);
			me->add_temp("canwu_lianti",2);
			me->add("qi",me->query("max_qi"));
			me->add("neili",me->query("max_qi"));
			me->improve_skill("jingang-liantishu",me->query_int(1)*10);
			me->improve_skill("xuedao-jing",me->query_int(1)*10);

			break;

		default:tell_object(me,YEL"\n你头朝下，不动如金刚，进入一种玄妙的状态.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"头朝下，埋入雪中，只余下双脚露在外面，姿势怪异，宛如僵尸.\n"NOR, ({}));

	//  remove_call_out("do_mo");
	  call_out("do_lianxi",3+random(3), me);

   } 
  else if (i>25
	  && random(j)<4
	//  && random(jobs)>1200
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$N原本有些动荡的真气，气血忽然奔走如水银般的，行走在奇经八脉之中。\n"NOR,me); 
         message_vision(HIW"\n$N心中顿时大喜，「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断练习领悟，终于领悟了血刀老祖所传授的金刚炼体术的奥秘！”\n"NOR,me); 
         log_file("quest/xdjglts", sprintf("%s(%s) 金刚炼体术解密成功！第%d次参悟，机缘巧合下，成功参悟金刚炼体术绝技的奥秘，随机幸运值：%d,当前随机值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/jglts/jingang/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/jglts/jingang/time",time());
		 me->set("quest/xd/jglts/jingang/pass",1);
		 me->delete_temp("canwu_lianti");
		 me->delete_temp("quest/xd/jglts");
		 me->delete_temp("quest/xd/jglts/jingang/lianti");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来这金刚炼体术诀真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟金刚炼体术诀绝技解密失败！\n"NOR,me); 
         log_file("quest/xdjglts", sprintf("%s(%s) 失败！参悟金刚炼体术第%d次失败，随机幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/jglts/jingang/fail",1),
		 i,
		 j,
         me->query("combat_exp"),));        
		 me->add("quest/xd/jglts/jingang/fail",1);
		 me->set("quest/xd/jglts/jingang/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_lianti");
		 me->delete_temp("quest/xd/jglts");
		 me->delete_temp("quest/xd/jglts/jingang/lianti");
		 return 1;
   }
	
}
