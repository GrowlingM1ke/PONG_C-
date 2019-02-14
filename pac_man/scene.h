#include <vector>
#include <memory>
#include "entity.h"

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual void load() = 0;
	std::vector<std::shared_ptr<Entity>> &getEnts();

protected:
	EntityManager _ents;
};