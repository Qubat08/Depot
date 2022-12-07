<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Event;
use App\Models\User;
use App\Http\Requests\StoreEventsRequest;
use Illuminate\Support\Facades\Auth;

class EventController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $eventsList = Event::orderBy('date', 'desc')->take(10)->get();
        
        return view('event.list', ['eventList' => $eventsList]);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('event.create');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(StoreEventsRequest $request)
    {
        if(!Auth::check())
            return redirect('login');
        
        $request->validated();

        $event = Event::make($request->input()); // à la place de create
        $event->save();

        return redirect()->route('event.show', ['event' => $event]);
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        return view('event.show', ['event'=> Event::findOrFail($id)]);
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        if(!Auth::check())
            return redirect('login');
        return view('event.edit',['event' => Event::findOrFail($id)]);
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(StoreEventsRequest $request, Event $event)
    {
        if(!Auth::check())
            return redirect('login');
        
        $request->validated();
        $event->update($request->input());
        return redirect()->route('event.show',['event'=>$event]);
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        if(!Auth::check())
        return redirect('login');
    
    $events = Event::findOrFail($id);
    $events->delete();
    return redirect()->route('event.index');
    }
}
