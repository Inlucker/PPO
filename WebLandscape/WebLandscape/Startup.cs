using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebLandscape
{
  public class Startup
  {
    public Startup(IConfiguration configuration)
    {
      Configuration = configuration;
    }

    public IConfiguration Configuration { get; }

    // This method gets called by the runtime. Use this method to add services to the container.
    public void ConfigureServices(IServiceCollection services)
    {
      services.AddControllers();
      services.AddSwaggerGen();
    }

    private readonly string swaggerBasePath = "api";

    // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
    public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
    {
      if (env.IsDevelopment())
      {
        app.UseDeveloperExceptionPage();
        //app.UseSwagger();
        //app.UseSwaggerUI();

        /*app.UseSwagger(c =>
        {
          c.RouteTemplate = swaggerBasePath + "/swagger/{documentName}/swagger.json";
        });

        app.UseSwaggerUI(c =>
        {
          c.SwaggerEndpoint($"/{swaggerBasePath}/swagger/v1/swagger.json", "APP API - v1");
          c.RoutePrefix = $"{swaggerBasePath}/swagger";
        });*/

        /*app.UseSwagger(c =>
        {
          c.RouteTemplate = "AnyWord/WordAny1/{documentname}/swagger.json";
        });
        app.UseSwaggerUI(c =>
        {
          c.SwaggerEndpoint("/AnyWord/WordAny1/v1/swagger.json", "My Cool API V1");
          c.RoutePrefix = "AnyWord/WordAny1";
        });*/

        app.UseSwagger(c =>
        {
          c.RouteTemplate = "api/v1/{documentname}/swagger.json";
        });
        app.UseSwaggerUI(c =>
        {
          c.SwaggerEndpoint("/api/v1/v1/swagger.json", "WebLandscape v1");
          c.RoutePrefix = "api/v1";
        });

        /*app.UseSwagger(c =>
        {
          c.RouteTemplate = "api/swagger/{documentname}/swagger.json";
        });
        app.UseSwaggerUI(c =>
        {
          c.SwaggerEndpoint("/api/swagger/v1/swagger.json", "v1");
          c.RoutePrefix = "api/swagger";
        });*/
      }

      app.UseHttpsRedirection();

      app.UseRouting();

      app.UseAuthorization();

      app.UseEndpoints(endpoints =>
      {
        endpoints.MapControllers();
      });
    }
  }
}
