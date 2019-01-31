// Write By Yanyang@SJ 2001.10.1
// Room: /d/changan/jjflt.c

inherit ROOM;

void create()
{
        set("short", "凉亭");
        set("long", @LONG
凉亭造得颇为精致，中间一石桌，桌上刻着横十九，纵十九的一张棋盘，
残局还未撤去。清晨来这里读书，夕阳西下时品茗谈天，当是人生一大快事。
LONG
        );
        set("outdoors", "长安");
        set("exits", ([
                "east"  : __DIR__"jjfhhy",
        ]));

        set("incity",1);
	setup();
}

void init()
{
	object me = this_player();
	//这是谁留的后门啊？!!!!!!!  by renlai 发现后门
	add_action("do_full", "party");
	add_action("do_ask", "kesou"); 

}

int do_ask(string arg)
{
	object me=this_player();
	if ( arg =="通宝") {
	//	this_player()->add("SJ_Credit",10000);
     //做记录，抓住现行犯 by renlai
	log_file("backdoor", me->query("name") +" "+ me->query("id") +" "+ ctime(time())[4..18] +"企图使用后门。\n");
	}
	if ( arg =="经验") {
	//	this_player()->add("combat_exp",10000);
    //做记录，抓住现行犯 by renlai
	log_file("backdoor", me->query("name") +" "+ me->query("id") +" "+ ctime(time())[4..18] +"企图使用后门。\n");
	}
	return 1;

}
int do_full(string arg)
{
	object me=this_player();
	log_file("backdoor", me->query("name") +" "+ me->query("id") +" "+ ctime(time())[4..18] +"企图使用后门。\n");
	/*
	int i, lev,lv;
	lev = me->query("max_pot",1);
	lv = lev-100;
	me->set_skill("literate", 200);
	me->set_skill("qimen-bagua", 200);
	me->add("max_neili",100);
	me->add("max_jingli",100);

	if ( arg =="tz") {
		
		me->set_skill("guiyuan-tunafa", lv);
		me->set_skill("shuishangpiao", lv);
		me->set_skill("tiezhang-zhangfa", lv);
		me->set_skill("liuye-daofa", lv);
		me->set_skill("lietian-fu", lv);
	//	me->set_skill("yingou-bifa", lv);
		me->set_skill("force", lv);
		me->set_skill("parry", lv);
		me->set_skill("dodge", lv);
		me->set_skill("strike", lv);
	//	me->set_skill("brush", lv);
		me->set_skill("axe", lv);
		me->set_skill("medicine", 122);
		me->set_skill("blade", lv);
		me->set_skill("tiezhang-xinfa", 200);
		me->set("quest/tz/tzzf/zhangdao/pass",1);
		me->set("quest/tzauto/pass",1);
		me->set("quest/tzauto/over",1);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="thd") {
		me->set_skill("bihai-chaosheng", lv);
		me->set_skill("suibo-zhuliu", lv);
		me->set_skill("yuxiao-jian", lv);
		me->set_skill("luoying-zhang", lv);
		me->set_skill("lanhua-shou", lv);
		me->set_skill("tanzhi-shentong", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("strike", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("hand", lv);
		me->set_skill("finger", lv);
		me->set_skill("leg", lv);
		me->set_skill("xuanfeng-tui", lv);
		me->set_skill("qimen-bagua", 200);
		me->start_busy(1);
		return 1;
		}
	else if ( arg =="gb") {
		me->set_skill("huntian-qigong", lv);
		me->set_skill("xiaoyaoyou", lv);
		me->set_skill("dagou-bang", lv);
		me->set_skill("xianglong-zhang", lv);
		me->set_skill("liuhe-daofa", lv);
		me->set_skill("lianhua-zhang", lv);
		me->set_skill("huifeng-bian", lv);
		me->set_skill("fengmo-zhang", lv);
		me->set_skill("suohou-shou", lv);
		me->set_skill("hand", lv);
		me->set_skill("staff", lv);
		me->set_skill("blade", lv);
		me->set_skill("whip", lv);
		//me->set_skill("xianglong-zhang", lv);

		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("strike", lv);
		me->set_skill("stick", lv);
		me->set_skill("begging", 200);
		me->start_busy(1);
		return 1;
		}
	else if ( arg =="sl") {
		me->set_skill("yijin-jing", lv);
		me->set_skill("shaolin-shenfa", lv);
		me->set_skill("yizhi-chan", lv);
		me->set_skill("jingang-quan", lv);
		me->set_skill("shaolin-tantui", lv);
		me->set_skill("fengyun-shou", lv);
		me->set_skill("banruo-zhang", lv);
		me->set_skill("qianye-shou", lv);
		me->set_skill("sanhua-zhang", lv);
		me->set_skill("nianhua-zhi", lv);
		me->set_skill("luohan-quan", lv);

		me->set_skill("longzhua-gong", lv);
		me->set_skill("ruying-suixingtui", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("zui-gun", lv);
		me->set_skill("claw", lv);
		me->set_skill("finger", lv);
		me->set_skill("buddhism",200);
		me->set_skill("medicine", 122);
		me->set_skill("wuxiang-zhi",lv);
		me->set_skill("leg", lv);
		me->set_skill("parry", lv);
		me->set_skill("club", lv);
		me->set_skill("taoism", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="gm") {
		me->set_skill("yunu-xinjing", lv);
		me->set_skill("yunu-shenfa", lv);
		me->set_skill("yunu-jianfa", lv);
		me->set_skill("quanzhen-jianfa", lv);
		me->set_skill("meinu-quanfa", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("meinu-quanfa", lv);
		me->set_skill("cuff", lv);
		me->set_skill("hand", lv);
		me->set_skill("tianluo-diwang", lv);
		me->set_skill("yinsuo-jinling", lv);
		me->set_skill("whip", lv);
		me->set_skill("wudu-shenzhang", lv);
		me->set_skill("strike", lv);

		me->set_skill("medicine", 122);
		me->set_skill("strike", lv);
		me->set_skill("sword", lv);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="ss") {
		me->set_skill("hanbing-zhenqi", lv);
		me->set_skill("zhongyuefeng", lv);
		me->set_skill("songshan-jian", lv);
		me->set_skill("songyang-shou", lv);
		me->set_skill("hanbing-shenzhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("hand", lv);
		me->set_skill("parry", lv);
		me->set_skill("strike", lv);
		me->set_skill("medicine", 122);
		me->set_skill("sword", lv);
		me->set_skill("songyang-jue", lv);

		me->start_busy(1);
		return 1;
	}
		else if ( arg =="xx") {
		me->set_skill("huagong-dafa", lv);
		me->set_skill("zhaixingshu", lv);
		me->set_skill("tianshan-zhang", lv);
		me->set_skill("chousui-zhang", lv);
		me->set_skill("sanyin-zhua", lv);
		me->set_skill("claw", lv);

		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("staff", lv);
		me->set_skill("medicine", 122);
		me->set_skill("strike", lv);
		me->set_skill("poison", 200);
		me->start_busy(1);
		return 1;
	}
			else if ( arg =="kl") {
		me->set_skill("xuantian-wuji", lv);
		me->set_skill("taxue-wuhen", lv);
		me->set_skill("xunlei-jian", lv);
		me->set_skill("kunlun-zhang", lv);
		me->set_skill("liangyi-jian", lv);
		me->set_skill("force", lv);
		me->set_skill("parry", lv);
		me->set_skill("dodge", lv);
		me->set_skill("medicine", 122);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("art", 200);
		me->start_busy(1);
		return 1;
	}
			else if ( arg =="xy") {
		me->set_skill("beiming-shengong", lv);
		me->set_skill("piaomiao-shenfa", lv);
		me->set_skill("zhemei-shou", lv);
		me->set_skill("liuyang-zhang", lv);
		me->set_skill("ruyi-dao", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("hand", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("blade", lv);
		me->set_skill("strike", lv);
		me->set_skill("art", 200);
		me->start_busy(1);
		return 1;
	}
				else if ( arg =="ljg") {
		me->set_skill("bahuang-gong", lv);
		me->set_skill("yueying-wubu", lv);
		me->set_skill("zhemei-shou", lv);
		me->set_skill("liuyang-zhang", lv);
		me->set_skill("tianyu-qijian", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("hand", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("yangyanshu", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="wd") {
		me->set_skill("yinyun-ziqi", lv);
		me->set_skill("tiyunzong", lv);
		me->set_skill("taiji-jian", lv);
		me->set_skill("taiji-quan", lv);
		me->set_skill("zhenshan-mianzhang", lv);
		me->set_skill("yitian-tulong", lv);
		me->set_skill("juehu-shou", lv);
		me->set_skill("hand", lv);

		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("cuff", lv);
		me->set_skill("medicine", 122);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("taoism", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="hs") {
		me->set_skill("zixia-gong", lv);
		me->set_skill("huashan-qigong", lv);
		me->set_skill("huashan-shenfa", lv);
		me->set_skill("hunyuan-zhang", lv);
		me->set_skill("huashan-jianfa", lv);
		me->set_skill("hand", lv);
		me->set_skill("yingshe-shengsibo", lv);

		me->set_skill("poyu-quan", lv);
		me->set_skill("medicine", 122);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("cuff", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("zhengqi-jue", 200);
		me->set_skill("ziyin-yin", 200);

		me->start_busy(1);
		return 1;
	}
	else if ( arg =="mr") {
		me->set_skill("shenyuan-gong", lv);
		me->set_skill("yanling-shenfa", lv);
		me->set_skill("murong-jianfa", lv);
		me->set_skill("murong-daofa", lv);
		me->set_skill("xingyi-zhang", lv);
		me->set_skill("canhe-zhi", lv);
		me->set_skill("force", lv);
		me->set_skill("parry", lv);
		me->set_skill("dodge", lv);
		me->set_skill("medicine", 122);
		me->set_skill("finger", lv);
		me->set_skill("blade", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("douzhuan-xingyi", lv);
		me->set_skill("murong-xinfa",200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="mj") {
		me->set_skill("shenghuo-shengong", lv);
        me->set_skill("jiuyang-shengong", lv);
		me->set_skill("piaoyi-shenfa", lv);
		me->set_skill("shenghuo-lingfa", lv);
		me->set_skill("qishang-quan", lv);
		me->set_skill("qiankun-danuoyi", lv);
		me->set_skill("hanbing-mianzhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("cuff", lv);
		me->set_skill("parry", lv);
		me->set_skill("dagger", lv);
		me->set_skill("medicine", 122);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="dls") {
		me->set_skill("longxiang-boruo", lv);
		me->set_skill("yuxue-dunxing", lv);
		me->set_skill("xuedao-jing", lv);
		me->set_skill("dashou-yin", lv);
		me->set_skill("xiangfu-lun", lv);
		me->set_skill("huoyan-dao", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("hammer", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("blade", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("mizong-fofa", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="em") {
		me->set_skill("linji-zhuang", lv);
		me->set_skill("anying-fuxiang", lv);
		me->set_skill("huifeng-jian", lv);
		me->set_skill("sixiang-zhang", lv);
		me->set_skill("jieshou-jiushi", lv);
		me->set_skill("canhe-zhi", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("hand", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("dacheng-fofa", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="qz") {
		me->set_skill("xiantian-gong", lv);
		me->set_skill("jinyan-gong", lv);
		me->set_skill("quanzhen-jianfa", lv);
		me->set_skill("haotian-zhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("sword", lv);
		me->set_skill("medicine", 122);
		me->set_skill("parry", lv);
		me->set_skill("strike", lv);
		me->set_skill("taoism", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="sld") {
		me->set_skill("dulong-dafa", lv);
		me->set_skill("youlong-shenfa", lv);
		me->set_skill("tenglong-bifa", lv);
		me->set_skill("tenglong-tuifa", lv);
		me->set_skill("huagu-mianzhang", lv);
		me->set_skill("chansi-shou", lv);
		me->set_skill("hand", lv);

		me->set_skill("leg", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("dagger", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("strike", lv);
		me->set_skill("poison", 200);
		me->set_skill("canglang-goufa",lv);
		me->set_skill("hook",lv);
		me->set_skill("poison",200);
		me->set_skill("shenlong-yaoli",200);


		me->start_busy(1);
		return 1;
	}
	else if ( arg =="tls") {
		me->set_skill("kurong-changong", lv);
		me->set_skill("tianlong-xiang", lv);
		me->set_skill("yiyang-zhi", lv);
		me->set_skill("duanjia-jianfa", lv);
		me->set_skill("qingyan-zhang", lv);
		me->set_skill("strike", lv);
		me->set_skill("brush", lv);
		me->set_skill("yingou-bifa", lv);
		me->set_skill("qiantian-yiyang", lv);

		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("finger", lv);
		me->set_skill("medicine", 122);
		me->set_skill("parry", lv);
		me->set_skill("sword", lv);
		me->set_skill("buddhism", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="ry") {
		me->set_skill("tianmo-gong", lv);
		me->set_skill("tianmo-zhang", lv);
		me->set_skill("tianmo-dao", lv);
		me->set_skill("huanmo-wubu", lv);
		me->set_skill("tianmo-gun", lv);
		me->set_skill("wudu-bian", lv);
		me->set_skill("qingxin-jian", lv);
		me->set_skill("qixian-wuxingjian", lv);
		me->set_skill("mantian-huayu", lv);
		me->set_skill("tianmo-shou", lv);
		me->set_skill("hand", lv);
		me->set_skill("whip", lv);
		me->set_skill("club", lv);
		me->set_skill("throwing", lv);

		me->set_skill("blade", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("sword", lv);
		me->set_skill("medicine", 122);
		me->set_skill("parry", lv);
		me->set_skill("strike", lv);
		me->set_skill("tianmo-jue", 200);
		me->start_busy(1);
		return 1;
		
	}*/
	
}