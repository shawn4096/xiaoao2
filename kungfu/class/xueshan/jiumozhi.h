


string ask_rmdf()
{	
	int i,j,t;
	object me = this_player();

	if (!me->query_temp("rmdf/askku"))
    {
		command("say 我虽然已然大彻大悟，但你贼胆包天的这里骚扰，难道不想活了！");
        return "哼哼！\n";
	}
	
	if (time()-me->query("quest/sl/rmdf/shoudao/time")<86400)
    {
		command("say 你来的太勤快了，禅宗讲究的是顿悟，你能知晓么？！");
        return "哈哈！\n";
	}

	i = 20;
	if(me->query("m-card-vip")) i =  18;
	if(me->query("y-card-vip")) i =  15;
	if(me->query("buyvip"))     i =  10;
	i=random(i);

	j=random(me->query("kar"));
	//t=random(me->query_skill("blade",1))/10;
	t=random(me->query("int"));
	command("say 少林七十二绝技乃是不传之秘，我当时心中有魔，无意中知晓了这些秘籍。\n");
	command("say 本以为这样足已经纵横天下，熟不料当时已经入了魔道。\n");
	command("say 多亏了段誉公子将我一身功力废掉，使得我心魔终于化解。\n");
	command("say 既然玄苦大师派你来寻我此事，也该到了将这门绝技回归少林的时候了。\n");
	command("say 你仔细听好了，能否领悟就看你的资质和缘分了。\n");
	command("whisper "+me->query("id"));
	command("say 以手做刀，运功于手少阳经，过三焦，上曲尺，然后聚集于寸关穴....。\n");
	command("say 你听懂了么?。\n");

	command("pat "+me->query("id"));
	if( i<3 
		&& me->query("kar")<31
		&& t >= 40
		&& j > 26 ) 
	{
		tell_object(me,HIY"\n你听了鸠摩智的指点，对燃木刀之手刀绝技的奥妙颇有心得。\n"NOR);
		tell_object(me,HIG"\n你试图将内息冲到劳工穴中，突然只觉手三阳经上一股热气直通双手，手上经脉不禁豁然一轻。\n"
			             +"你下意识地顺手一挥，一阵破空声传来，波的一声，劲力强劲的很。\n"
						 +"你终于领悟了这门燃木刀之手刀绝技绝技的运用法门。心中大喜之下，后续招式连绵不绝而出。\n"
						 +"这招式劲力运使法门第一次通行时甚是艰难，任督两脉既通，经脉熟悉后，势如破竹。\n"
						 +"顷刻之间，你手上经脉尽通，领悟了燃木刀之手刀绝技绝技。\n"NOR);
		me->set("quest/sl/rmdf/shoudao/pass",1);
		log_file("quest/rmdfshoudao", sprintf("%8s(%8s) 失败%d次后，学到燃木刀之手刀绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前先天悟性取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/sl/rmdf/shoudao/fail"),i,j,t,me->query("combat_exp")) );
		command("haha"+me->query("id"));
		me->set("title",HIY"少林寺"+HIR"燃木刀法传人"NOR);
		me->delete_temp("rmdf");
		return "恭喜解密燃木刀之手刀绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/rmdfshoudao", sprintf("%8s(%8s) 解密燃木刀之手刀绝技绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前先天悟性取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/sl/rmdf/shoudao/fail"),i,j,t,me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了鸠摩智的指点，可是对燃木刀之手刀绝技的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/sl/rmdf/shoudao/fail",1);
		me->set("quest/sl/rmdf/shoudao/time",time());
		me->start_busy(1+random(3));
		me->delete_temp("rmdf");
		return "非常遗憾解密燃木刀之手刀绝技失败"+me->query("quest/sl/rmdf/shoudao/fail")+"次。\n";
	}
}


string ask_jiasha()
{
        object me=this_player() , armor;
        int i;

        if ((string)me->query("family/family_name") != "大轮寺")
                i = 5;
        else
                i = 1;

        if(me->query_temp("xs/xs_job") >= 1*i) {
                armor = present("shisan longxiang", this_object());
                if(!objectp(armor))     armor = unew(ARMOR_D("lx_cloth"));
                if(!objectp(armor))
                        return "十三龙象袈裟现在不在我手里。";  

                command("remove shisan longxiang");
                armor->move(me);
                command("emote 给你一件十三龙象袈裟。");
                command("wear jiasha");
                me->set_temp("xs/xs_job",0);
        }
        else
                return "心动不如行动，拿点实际成绩来给我看嘛。\n";

        return "好，这件十三龙象袈裟你拿去吧！";
}