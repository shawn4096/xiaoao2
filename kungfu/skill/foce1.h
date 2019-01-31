int valid_public(object me)
{
      mapping skl = me->query_skills();
      string *sk;
      int i;
      string skl_name = explode(__FILE__, "/")[<1][0..<3];

      if (!mapp(skl)) return 1;
      sk = keys(skl);
      i = sizeof(sk);
      while (i--) {
        if (sk[i] == "jiuyang-shengong" || sk[i] == "jiuyin-zhengong" || sk[i] == "lengquan-shengong" || sk[i] == "shenzhao-jing"
        || sk[i] == "hamagong" || sk[i] == "kuihua-shengong"|| sk[i] == "taixuan-gong" || sk[i] == "xixing-dafa" || sk[i] == "beiming-shengong"
        || sk[i] == "bahuang-gong" || sk[i] == "xiaowu-xianggong" || sk[i] == "xiantian-gong" || sk[i] == "tianmo-gong" || sk[i] == "taiji-shengong"
        || sk[i] == "yunu-xinjing"|| sk[i] == "huashan-qigong"|| sk[i] == "zixia-gong"|| sk[i] == "yinyun-ziqi"|| sk[i] == "bihai-chaosheng"
        || sk[i] == "hanbing-zhenqi"|| sk[i] == "longxiang-boruo"|| sk[i] == "huntian-qigong"|| sk[i] == "xuantian-wuji"|| sk[i] == "guiyuan-tunafa"
        || sk[i] == "yijin-jing"|| sk[i] == "qiantian-yiyang"|| sk[i] == "kurong-changong"|| sk[i] == "linji-zhuang"|| sk[i] == "huagong-dafa"
        || sk[i] == "shenyuan-gong"|| sk[i] == "shenghuo-shengong") continue;
        
        if (sk[i] != skl_name && SKILL_D(sk[i])->valid_enable("force"))
          return notify_fail("你不散掉"+to_chinese(sk[i])+"，如何能修习"+to_chinese(skl_name)+"。\n");
      }
      


      return 1;
}
int force_effect(string skill)
{	
	//对抗效果是从-3 -> 3，分别是受伤最重到受伤很轻，唯一一个例外，是jiuyin-zhengong，吸收
	//当然，本身有吸收效果
	//不同内功性质的内功有相生相克的效果，dulong-dafa属于阴寒内功，
	//阳性的内功对抗这个的效果就好，但是阴性内功就无法对抗，还要附加伤害
	//没有列出来的内功，算是中性内功，无法区分了。:(
        switch (skill)
        {//阴阳属性判断
                case "jiuyang-shengong" : return 9;
				case "hamagong"         : return 9;
                case "yijin-jing"       : return 8;
				case "longxiang-boruo"  : return 2;
                case "huntian-qigong"   : return 3;
                case "qiantian-yiyang"  : return 3;
                case "guiyuan-tunafa"   : return 3;
                case "kurong-changong"  : return 1;
                case "shenghuo-shengong": return 2;
                case "huashan-qigong"   : return 2;
                case "huntian-qigong"   : return 0;
                case "linji-zhuang"     : return -1;
                case "shenzhao-jing"    : return -1;
                case "shenyuan-gong"    : return -1;
                
                case "dulong-dafa"      : return -2;
                case "huagong-dafa"     : return -2;
                case "xuantian-wuji"    : return -4;
                case "yunu-xinjing"     : return -3;
                case "hanbing-zhenqi"   : return -3;
                case "bihai-chaosheng"  : return -3;
				case "zixia-gong"       : return -2;
				case "yinyun-ziqi"      : return -2;
				case "lengquan-shengong"  : return -4;
				case "kuihua-shengong"  : return -4;
                case "jiuyin-zhengong"  : return -4;
                default: return 1;
        }
}