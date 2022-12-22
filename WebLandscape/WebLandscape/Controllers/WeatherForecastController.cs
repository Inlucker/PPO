using Microsoft.Extensions.Logging;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using WebLandscape.Models;// пространство имен класса User
using WebLandscape.ViewModels; // пространство имен моделей RegisterModel и LoginModel

namespace WebLandscape.Controllers
{
	[ApiController]
	//[Route("api/v1/[controller]")]
	//[Route("[controller]")]
	[Route("")]
	public class WeatherForecastController : ControllerBase
	{
		private static readonly string[] Summaries = new[]
		{
		"Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
	};

		private readonly ILogger<WeatherForecastController> _logger;

		public WeatherForecastController(ILogger<WeatherForecastController> logger)
		{
			_logger = logger;
		}

		[HttpGet("api/v1/[controller]")]
		public IEnumerable<WeatherForecast> Get()
		{
			return Enumerable.Range(1, 5).Select(index => new WeatherForecast
			{
				Date = DateTime.Now.AddDays(index),
				TemperatureC = new Random().Next(-20, 55),
				Summary = Summaries[new Random().Next(Summaries.Length)]
			})
			.ToArray();
		}


		[HttpGet("[controller]")]
		public IEnumerable<WeatherForecast> Get2()
		{
			return Enumerable.Range(1, 5).Select(index => new WeatherForecast
			{
				Date = DateTime.Now.AddDays(index),
				TemperatureC = new Random().Next(-20, 55),
				Summary = Summaries[new Random().Next(Summaries.Length)]
			})
			.ToArray();
		}
	}
}
