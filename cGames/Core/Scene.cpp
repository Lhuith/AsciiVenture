void Scene::UpdateObjects()
{
	if (objects.size() != 0)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			objects.at(i)->Update();
		}
	}
}

void Scene::InitObjects()
{
	if (objects.size() != 0)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			InitObjectAt(i);
		}
	}
}

void Scene::InitObjectAt(int i)
{
	if (objects.at(i) != nullptr)
	{
		objects.at(i)->t.SetWorldTransform(this->WorldTransform);
		objects.at(i)->SetLocalArray(this->objects);
		objects.at(i)->Init();
	}
}

void Scene::InitObjectAt(Object *o)
{
	if (std::find(this->objects.begin(), this->objects.end(), o) != this->objects.end())
	{
		o->t.SetWorldTransform(this->WorldTransform);
		o->SetLocalArray(this->objects);
		o->Init();
	}
}

WORD Scene::SortAttrbute(char c)
{
	if (c == '^')
	{
		return 0x000F | 0x0090;
	}
	else if (c == 'i')
	{
		return 0x0002;
	}
	else if (c == '1')
	{
		return 0x0000;
	}
	else if (c == '#')
	{
		return 0x0070;
	}
	else if (c == '.')
	{
		return 0x0060;
	}
	else if (c == '1')
	{
		return 0x0000;
	}
	else
	{
	}

	return 0x0007;
}

void Scene::AssignAttribute()
{
	for (int x = 0; x < this->width; x++)
		for (int y = 0; y < this->height; y++)
		{
			this->attributes[y * this->width + x].Attributes = SortAttrbute(this->map[y * this->width + x]);
			this->attributes[y * this->width + x].Char.UnicodeChar = this->map[y * this->width + x];
		}
}