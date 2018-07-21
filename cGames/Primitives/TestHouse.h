
Scene TestHome(
 L"TestHouse",
 L"###################################"
  "#|oooooo|                    |ooo|#"
  "#|oooooo|                    |ooo|#"
  "#                                 #"
  "#                                 #"
  "#                                 #"
  "#                                 #"
  "#               |11|              #"
  "###################################",
  1,
  35,
  9,
  Vector2(-20, -4),{
	new Object(Transform(Vector2(25 , 5)), L"Beer Seller", {std::make_shared<cSprite>
	(L" o "
      " █ "
      "   ", 
    Vector2(3, 3), Vector2(1, 1), 0x000F)})
  }
  );