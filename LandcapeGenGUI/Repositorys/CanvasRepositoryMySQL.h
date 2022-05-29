#ifndef CANVASREPOSITORYMYSQL_H
#define CANVASREPOSITORYMYSQL_H

#include "ICanvasRepository.h"
#include "Errors/RepositoryErrors.h"

class CanvasRepositoryMySQL : public ICanvasRepository
{
public:
    CanvasRepositoryMySQL();
    virtual ~CanvasRepositoryMySQL() = default;

    virtual shared_ptr<CanvasBL> getCanvas(int id) override;
    shared_ptr<CanvasBL> getCanvas(string name);
    vector<pair<int, string>> getCanvasesByUid(int u_id);
    virtual void addCanvas(CanvasBL& canvas) override;
    virtual void deleteCanvas(int id) override;
    virtual void updateCanvas(CanvasBL& canvas_bl, int id) override;

    void test(string &str);

protected:
    string m_schema;
};

#endif // CANVASREPOSITORYMYSQL_H
